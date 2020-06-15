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
    oss <<"d";
    oss << gen_tref(env, stmt, *(stmt.lhsNode->tRefNode));
    oss << "+=" ;
    oss << gen_rhs(env, stmt, *stmt.rhsNode);
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
        case Operation::times:
            RHS.lnode->gradNode = new StmtNode;
            RHS.lnode->gradNode->rhsNode = new RHSNode;
            RHS.lnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.lnode->gradNode->rhsNode->op = Operation::times;
            RHS.lnode->gradNode->rhsNode->lnode = RHS.gradNode->rhsNode;
            RHS.lnode->gradNode->rhsNode->rnode = RHS.rnode;
            // Merge Variable ! 

            RHS.rnode->gradNode = new StmtNode;
            RHS.rnode->gradNode->rhsNode = new RHSNode;
            RHS.rnode->gradNode->rhsNode->type = RHSType::binary;
            RHS.rnode->gradNode->rhsNode->op = Operation::times;
            RHS.rnode->gradNode->rhsNode->lnode = RHS.gradNode->rhsNode;
            RHS.rnode->gradNode->rhsNode->rnode = RHS.lnode;
            // Merge Variable ! 
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