#ifndef MOCK_SOLUTION_H
#define MOCK_SOLUTION_H

#include "adt.h"
#include "backend.h"
#include <json/json.h>
void get_env_from_json(Json::Value value, Env & env);
void check_env(Env & env);
void mock_env_example(Env& env);
void mock_root_example(RootNode& root);
void mock_env_case1(Env& env);
void mock_root_case1(RootNode& root);
void mock_env_case4(Env& env);
void mock_root_case4(RootNode& root);
void mock_env_case5(Env& env);
void mock_root_case5(RootNode& root);
void mock_env_case6(Env& env);
void mock_root_case6(RootNode& root);
void mock_env_case7(Env& env);
void mock_root_case7(RootNode& root);
void mock_env_case10(Env& env);
void mock_root_case10(RootNode& root);
#endif