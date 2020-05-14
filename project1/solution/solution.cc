#include "hw2c.tab.c"
#include "lex.yy.c"
#include "solution.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <json/json.h>

extern RootNode * root;

int main() {
    Json::Reader reader;
    Json::Value cases;

    vector<string> paths;
    paths.push_back("./cases/example.json");
    for (int i = 0; i <= 10; i++) {
        paths.push_back("./cases/case" + to_string(i) + ".json");
    }

    for (int i = 0; i < paths.size(); i++) {
        ifstream file(paths[i]);
        if (reader.parse(file, cases)) {
            Env env;
            string path_example;
            get_env_from_json(cases, env);
            yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
            yyparse(&env);
            string save_path = "./kernels/"+env.name+".cc";
            gen_and_save(save_path, env, *root);
        }
    }
}

void check_env(Env & env)
{
    cout << "Env name: " << env.name << endl;
    cout << "Type: " << (env.isInt?"int":"float") << endl;
    cout << "Tensors: " << endl;
    for (int i = 0; i < env.tensors.size(); ++i)
    {
        cout << "    " << env.tensors[i].name << '<' ;
        for (int j = 0; j < env.tensors[i].shape.size(); ++j)
        {
            cout <<  env.tensors[i].shape[j] << ' ';
        }
    }
    cout << endl;
}

void get_env_from_json(Json::Value value, Env & env) 
{
    env.name = value["name"].asString();
    if (value["data_type"].asString() == "float") 
    {
        env.isInt = false;
    }
    else env.isInt = true;

    set<string> params;

    for (int i = 0; i < value["ins"].size(); ++i)
    {
        Tensor t;
        t.name = value["ins"][i].asString();
        if (params.find(t.name) == params.end())
        {
            env.tensors.push_back(t);
            params.insert(t.name);
        }
    }

    for (int i = 0; i < value["outs"].size(); ++i)
    {
        Tensor t;
        t.name = value["outs"][i].asString();
        if (params.find(t.name) == params.end())
        {
            env.tensors.push_back(t);
            params.insert(t.name);
        }
    }

}