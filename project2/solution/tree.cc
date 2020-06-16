#include "tree.h"
#include "backend.h"

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void print_info(Env & env, StmtNode & stmt)
{
    vector<StmtNode*> target;
    queue<RHSNode*> myqueue;
    myqueue.push(stmt.rhsNode);
    while(!myqueue.empty())
    {
        RHSNode * curr = myqueue.front();  myqueue.pop();
        switch (curr->type)
        {
        case RHSType::binary:
            myqueue.push(curr->lnode);
            myqueue.push(curr->rnode);
            break;

        case RHSType::uniary:
            myqueue.push(curr->lnode);
            break;

        case RHSType::tref:
            if (env.tensors[curr->tRefNode->paramterIndex].require_grad)
            {
                target.push_back(curr->gradNode);
            }
            break;
        
        default:
            break;
        }
    }

    for (int i=0;i<target.size();++i)
    {
        cout << gen_cal(env, *target[i]) <<endl;
    }
}

string gen_cal(Env & env, StmtNode & stmt)
{
    ostringstream oss;
    // Left
    //Tensor & curr = env.tensors[stmt.lhsNode->tRefNode->paramterIndex];
    // "name": "grad_case1",
    // "ins": ["A", "B"],
    // "outs": ["C"],
    // "data_type": "float",
    // "kernel": "C<4, 16>[i, j] = A<4, 16>[i, j] * B<4, 16>[i, j] + 1.0;",
    // "grad_to": ["A"]

    // current : dA<4,16>[i,j] += B<4,16>[i,j] * C<4,16>[i,j];

    // Next to do : dA<4,16>[i,j] += B<4,16>[i,j] * dC<4,16>[i,j]; (看 (is_out)?"d":"")

    // Second Next to do : 完整的for代码

    // Third Next to do: dB[i+1,j] += dA[i,j]/3.0 ---> dB[u,j] += dA[u-1,j]/3.0 (令u=i+1)
    // case 6:  dB<2, 16, 7, 7>[n, c, p + r, q + s] = dA<2, 8, 5, 5>[n, k, p, q] * C<8, 16, 3, 3>[k, c, r, s];",
    //  ----> 令h = p + r ; r = h - p 所有单独的r都用代入h-p代入
    //  ----> 令w = q + s ; s = w - q 同上

    // dB<2, 16, 7, 7>[n, c, h, w] = dA<2, 8, 5, 5>[n, k, p, q] * C<8, 16, 3, 3>[k, c, h - p, w - q];"

    oss <<"d";
    oss << gen_tref(env, *(stmt.lhsNode->tRefNode));
    oss << "+=" ;
    oss << gen_rhs(env, *stmt.rhsNode);
    return oss.str();
}

void gen_grad(Env& env, StmtNode& stmt)
{
    stmt.rhsNode->gradNode = new StmtNode;
    stmt.rhsNode->gradNode->rhsNode = new RHSNode;
    stmt.rhsNode->gradNode->rhsNode->type = RHSType::tref;
    stmt.rhsNode->gradNode->rhsNode->tRefNode = stmt.lhsNode->tRefNode;
    backprop(env, *stmt.rhsNode);
}

void backprop(Env& env, RHSNode& RHS)
{
    switch (RHS.type)
    {
    case RHSType::binary:
        switch (RHS.op)
        {
        case Operation::plus:
            RHS.lnode->gradNode = RHS.gradNode;
            RHS.rnode->gradNode = RHS.gradNode;
            break;
                
        case Operation::minus:
            RHS.lnode->gradNode = RHS.gradNode;
            RHS.rnode->gradNode = new StmtNode;
            RHS.rnode->gradNode->rhsNode = new RHSNode;
            RHS.rnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.rnode->gradNode->rhsNode->op = Operation::times;
            RHS.rnode->gradNode->rhsNode->rnode = RHS.gradNode;
            RHS.rnode->gradNode->rhsNode->lnode = new RHSNode;
            RHS.rnode->gradNode->rhsNode->lnode.type = RHSType::constref;
            RHS.rnode->gradNode->rhsNode->lnode->constNode = new ConstNode;
            RHS.rnode->gradNode->rhsNode->lnode->constNode.isInt = true;
            RHS.rnode->gradNode->rhsNode->lnode->constNode.intVal = -1;
            break;

        case Operation::times:
            RHS.lnode->gradNode = new StmtNode;
            RHS.lnode->gradNode->rhsNode = new RHSNode;
            RHS.rnode->gradNode = new StmtNode;
            RHS.rnode->gradNode->rhsNode = new RHSNode;
                
            RHS.lnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.lnode->gradNode->rhsNode->op = Operation::times;
            RHS.lnode->gradNode->rhsNode->lnode = RHS.gradNode->rhsNode;
            RHS.lnode->gradNode->rhsNode->rnode = RHS.rnode;

            RHS.rnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.rnode->gradNode->rhsNode->op = Operation::times;
            RHS.rnode->gradNode->rhsNode->lnode = RHS.gradNode->rhsNode;
            RHS.rnode->gradNode->rhsNode->rnode = RHS.lnode;
            // Merge Variable ! 
            break;
                
        case Operation::divide:
            RHS.lnode->gradNode = new StmtNode;
            RHS.lnode->gradNode->rhsNode = new RHSNode;
            RHS.rnode->gradNode = new StmtNode;
            RHS.rnode->gradNode->rhsNode = new RHSNode;
            
            RHS.lnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.lnode->gradNode->rhsNode->op = Operation::divide;
            RHS.lnode->gradNode->rhsNode->lnode = RHS.gradNode->rhsNode;
            RHS.lnode->gradNode->rhsNode->rnode = RHS.rnode;
            
            RHS.rnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.rnode->gradNode->rhsNode->op = Operation::times;
            RHS.rnode->gradNode->rhsNode->lnode = new RHSNode;
            RHS.rnode->gradNode->rhsNode->lnode->type = RHSType::constref;
            RHS.rnode->gradNode->rhsNode->lnode->constNode = new ConstNode;
            RHS.rnode->gradNode->rhsNode->lnode->constNode.isInt = true;
            RHS.rnode->gradNode->rhsNode->lnode->constNode.intVal = -1;
                
            RHSNode* mynode = new RHSNode; //right child(tree)
            mynode->op = Operation::divide;
            mynode->lnode = new RHSNode;
            mynode->lnode->op = Operation::times;
            mynode->lnode->lnode = RHS.lnode;
            mynode->lnode->rnode = RHS.gradNode->rhsNode;
            mynode->rnode->lnode = RHS.rnode;
            mynode->rnode->rnode = RHS.rnode;
            RHS.rnode->gradNode->rhsNode->rnode = mynode;
            break;
        default:
            cerr<<"Not Implemented!"<<endl;
            break;
        }

        backprop(env, *RHS.lnode);
        backprop(env, *RHS.rnode);
    break;

    case RHSType::uniary:
        RHS.lnode->gradNode = RHS.gradNode;
        backprop(env, *RHS.lnode);
    break;

    case RHSType::tref:
    if (env.tensors[RHS.tRefNode->paramterIndex].require_grad)
        RHS.gradNode->lhsNode = new LHSNode;
        RHS.gradNode->lhsNode->tRefNode = RHS.tRefNode;
    break;
    
    default:
        break;
    }
}
