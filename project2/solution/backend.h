#ifndef BACKEND_H
#define BACKEND_H

#include "adt.h"
void gen_and_save(string path, Env& env, RootNode& root);
string gen_parameters(Env& env);
string gen_body(Env& env, RootNode& root);
string gen_loop(Env& env, StmtNode& stmt, int loop);
string gen_rhs(Env& env, RHSNode& rhsNode);
string gen_tref(Env& env, TRefNode& tRefNode);
string gen_sref(Env& env, SRefNode& sRefNode);
#endif