#ifndef TREE_H
#define TREE_H

#include "adt.h"
void gen_grad(Env& env, StmtNode& stmt);
void backprop(Env& env, RHSNode& RHS);


// To be modified
void print_info(Env & env, StmtNode & stmt);
string gen_cal(Env & env, StmtNode & stmt);
#endif