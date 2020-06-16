#ifndef BACKEND_H
#define BACKEND_H

#include "adt.h"
void gen_and_save(string path, Env& env, RootNode& root);
void replace_check(Env& env, RootNode& root);
string get_op_string(Operation op);
string gen_parameters(Env& env);
string gen_body(Env& env, RootNode& root);
string gen_loop(Env& env, StmtNode& stmt, int loop);
string gen_replace_expr(StmtNode& stmt, ReplacementNode& replacement);
string gen_replace_if(Env& env, StmtNode& stmt, int loop);
string gen_real_expr(Env& env, StmtNode& stmt, int loop);
string gen_lhs(Env& env, StmtNode& stmt);
string gen_rhs(Env& env, StmtNode& stmt, RHSNode& rhsNode);
string gen_tref(Env& env, StmtNode& stmt, TRefNode& tRefNode);
string gen_sref(Env& env, SRefNode& sRefNode);
#endif