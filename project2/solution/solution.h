#ifndef SOLUTION_H
#define SOLUTION_H

#include "adt.h"
#include "backend.h"
#include "tree.h"
#include <json/json.h>
void get_env_from_json(Json::Value value, Env & env);
void check_env(Env & env);
#endif