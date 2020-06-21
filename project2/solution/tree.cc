#include "tree.h"

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

AListNode * _fork_AListNode(AListNode * source)
{
    if (source == NULL) return NULL;
    AListNode * dest = new AListNode();
    for (int i=0;i<source->idExprList.size();i++)
    {
        dest->idExprList.push_back(new IdExprNode(*source->idExprList[i]));
        cout<<".."<<endl;
        // if (dest->idExprList[i]->op.size()==1) {
        //     cout<<dest->idExprList[i]->ids[0];
        //     cout<<get_op_string(dest->idExprList[i]->op[0]);
        //     cout<<dest->idExprList[i]->num[0];
        // }
    }
    return dest;
}

TRefNode * _fork_TRefNode(TRefNode * source)
{
    if (source == NULL) return NULL;
    cout<<"+"<<endl;
    TRefNode * dest = new TRefNode(*source);
    dest->aListNode = _fork_AListNode(source->aListNode);
    cout<<"+"<<endl;
    return dest;
}

RHSNode * _fork_RHSNode(RHSNode * source)
{
    if (source == NULL) return NULL;
    RHSNode * dest = new RHSNode(*source);
    switch (source->type)
    {
        case RHSType::binary:
            dest -> lnode = _fork_RHSNode(source->lnode);
            dest -> rnode = _fork_RHSNode(source->rnode);
            break;
            
        case RHSType::uniary:
            dest -> lnode = _fork_RHSNode(source->lnode);
            break;
            
        case RHSType::tref:
            dest -> tRefNode = _fork_TRefNode(source->tRefNode);
            break;
            
        default:
            break;
    }
    return dest;
}

LHSNode * _fork_LHSNode(LHSNode * source)
{
    if (source == NULL) return NULL;
    LHSNode * dest = new LHSNode(*source);
    cout<<"-"<<endl;
    dest -> tRefNode = _fork_TRefNode(source->tRefNode);
    cout<<"-"<<endl;
    return dest;
}

StmtNode * _fork(StmtNode * source)
{
    if (source == NULL) return NULL;
    StmtNode * dest = new StmtNode(*source);
    cout<<"?"<<endl;
    dest->lhsNode = _fork_LHSNode(source->lhsNode);
    cout<<"?"<<endl;
    dest->rhsNode = _fork_RHSNode(source->rhsNode);
    //cout<<"?"<<endl;
    return dest;
}


RootNode * gen_grad_root(Env & env, RootNode & root)
{
    cout<<"begin_gen_grad_root"<<endl;
    RootNode * grad_root= new RootNode();
    queue<RHSNode*> myqueue;
    for (int i =0;i<root.stmtNodes.size();i++)
    {
        myqueue.push(root.stmtNodes[i]->rhsNode);
    }
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
                    cout<<curr->gradNode<<endl;
                    grad_root->stmtNodes.push_back(_fork(curr->gradNode));
                }
                break;
                
            default:
                break;
        }
    }
    return grad_root;
}


string gen_cal(Env & env, StmtNode & stmt)
{
    ostringstream oss;
    oss << gen_lhs(env, stmt);
    oss << "+=" ;
    oss << gen_rhs(env, stmt, *stmt.rhsNode);
    return oss.str();
}

void gen_grad(Env& env, StmtNode& stmt)
{
    stmt.rhsNode->gradNode = new StmtNode();
    stmt.rhsNode->gradNode->rhsNode = new RHSNode();
    stmt.rhsNode->gradNode->rhsNode->type = RHSType::tref;
    stmt.rhsNode->gradNode->rhsNode->tRefNode = stmt.lhsNode->tRefNode;
    for (int i=0;i<stmt.variables.size();i++)
    {
        //cout<<stmt.variables[i].name<<"["<<stmt.variables[i].lowerBound<<" , "<<stmt.variables[i].upperBound<<")"<<endl;
        if (!stmt.variables[i].complex)
            stmt.rhsNode->gradNode->variables.push_back(stmt.variables[i]);
    }
    backprop(env, *stmt.rhsNode);
}

void backprop(Env& env, RHSNode& RHS)
{
    switch (RHS.type)
    {
        case RHSType::binary:
        {
            switch (RHS.op)
            {
                case Operation::plus:
                    RHS.lnode->gradNode = _fork(RHS.gradNode);
                    RHS.rnode->gradNode = _fork(RHS.gradNode);
                    break;
                    
                case Operation::minus:
                    RHS.lnode->gradNode = _fork(RHS.gradNode);
                    RHS.rnode->gradNode = new StmtNode();
                    RHS.rnode->gradNode->rhsNode = new RHSNode();
                    RHS.rnode->gradNode->rhsNode->type = RHSType::binary;
                    RHS.rnode->gradNode->rhsNode->op = Operation::times;
                    RHS.rnode->gradNode->rhsNode->rnode = RHS.gradNode->rhsNode;
                    RHS.rnode->gradNode->rhsNode->lnode = new RHSNode();
                    RHS.rnode->gradNode->rhsNode->lnode->type = RHSType::constref;
                    RHS.rnode->gradNode->rhsNode->lnode->constNode = new ConstNode();
                    RHS.rnode->gradNode->rhsNode->lnode->constNode->isInt = true;
                    RHS.rnode->gradNode->rhsNode->lnode->constNode->intVal = -1;
                    break;
                    
                case Operation::times:
                    RHS.lnode->gradNode = new StmtNode();
                    RHS.lnode->gradNode->rhsNode = new RHSNode();
                    RHS.rnode->gradNode = new StmtNode();
                    RHS.rnode->gradNode->rhsNode = new RHSNode();
                    
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
                {
                    RHS.lnode->gradNode = new StmtNode();
                    RHS.lnode->gradNode->rhsNode = new RHSNode();
                    RHS.lnode->gradNode->rhsNode->type = RHSType::binary;
                    RHS.lnode->gradNode->rhsNode->op = Operation::divide;
                    RHS.lnode->gradNode->rhsNode->lnode = RHS.gradNode->rhsNode;
                    RHS.lnode->gradNode->rhsNode->rnode = RHS.rnode;
                    
                    RHS.rnode->gradNode = new StmtNode();
                    // RHS.rnode->gradNode->rhsNode = new RHSNode;
                    // RHS.rnode->gradNode->rhsNode->type = RHSType::binary;
                    // RHS.rnode->gradNode->rhsNode->op = Operation::times;
                    // RHS.rnode->gradNode->rhsNode->lnode = new RHSNode;
                    // RHS.rnode->gradNode->rhsNode->lnode->type = RHSType::constref;
                    // RHS.rnode->gradNode->rhsNode->lnode->constNode = new ConstNode;
                    // RHS.rnode->gradNode->rhsNode->lnode->constNode->isInt = true;
                    // RHS.rnode->gradNode->rhsNode->lnode->constNode->intVal = -1;
                    
                    // RHSNode* mynode = new RHSNode;
                    // mynode->type = RHSType::binary;
                    // mynode->op = Operation::divide;
                    // mynode->lnode = new RHSNode;
                    // mynode->lnode->type = RHSType::binary;
                    // mynode->lnode->op = Operation::times;
                    // mynode->lnode->lnode = RHS.lnode;
                    // mynode->lnode->rnode = RHS.gradNode->rhsNode;
                    // mynode->rnode->lnode = RHS.rnode;
                    // mynode->rnode->rnode = RHS.rnode;
                    // RHS.rnode->gradNode->rhsNode->rnode = mynode;
                    break;
                }
                    
                default:
                    cerr<<"Not Implemented!"<<endl;
                    break;
            }
            
            RHS.lnode->gradNode->variables = RHS.gradNode->variables;
            RHS.rnode->gradNode->variables = RHS.gradNode->variables;
            backprop(env, *RHS.lnode);
            backprop(env, *RHS.rnode);
            break;
        }
            
        case RHSType::uniary:
        {
            RHS.lnode->gradNode = RHS.gradNode;
            RHS.lnode->gradNode->variables = RHS.gradNode->variables;
            backprop(env, *RHS.lnode);
            break;
        }
            
        case RHSType::tref:
        {
            if (env.tensors[RHS.tRefNode->paramterIndex].require_grad)
            {
                RHS.gradNode->lhsNode = new LHSNode();
                RHS.gradNode->lhsNode->tRefNode = RHS.tRefNode;
            }
            break;
        }
            
        default:
        {
            break;
        }
    }
}
