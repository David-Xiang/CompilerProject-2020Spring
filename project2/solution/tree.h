#ifndef TREE_H
#define TREE_H

#include "adt.h"
#include "backend.h"
void gen_grad(Env& env, StmtNode& stmt);
void backprop(Env& env, RHSNode& RHS);


// To be modified
string gen_cal(Env & env, StmtNode & stmt);
RootNode * gen_grad_root(Env & env, RootNode & root);
#endif