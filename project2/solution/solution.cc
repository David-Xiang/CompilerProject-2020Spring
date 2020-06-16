#include "hw2c.tab.c"
#include "lex.yy.c"
#include "solution.h"
#include "mock_replace_index.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <json/json.h>

extern RootNode * root;

int main() {
    // mock_replace_index_main();
    Json::Reader reader;
    Json::Value cases;

    vector<string> paths;
    for (int i = 1; i <= 10; i++) {
        
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
            //check_env(env);
            
            for (int j = 0; j < root->stmtNodes.size(); j++) {
                gen_grad(env, *(root->stmtNodes[j]));
            }
            RootNode * gradroot = gen_grad_root(env, *root);
            cout<<"gen_grad_root_end"<<endl;
            replace_check(env, *gradroot);

            gen_and_save(save_path, env, *gradroot);
            // for (int j = 0; j < gradroot->stmtNodes.size(); j++) {
            //     cout<<gen_cal(env, *(gradroot->stmtNodes[j]))<<endl;
            // }
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
        cout << "require_grad:" << ((env.tensors[i].require_grad)?"yes":"no") << ' ' ;
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
        Tensor t;t.require_grad=false;t.is_out=false;
        t.name = value["ins"][i].asString();
        if (params.find(t.name) == params.end())
        {
            env.tensors.push_back(t);
            params.insert(t.name);
        }
    }

    for (int i = 0; i < value["outs"].size(); ++i)
    {
        Tensor t;t.require_grad=false;t.is_out=true;
        t.name = value["outs"][i].asString();
        if (params.find(t.name) == params.end())
        {
            env.tensors.push_back(t);
            params.insert(t.name);
        }
    }

    for (int i = 0; i < value["grad_to"].size(); ++i)
    {
        string gname = value["grad_to"][i].asString();
        for (int j = 0 ; j<env.tensors.size() ; j++)
        {
            if (env.tensors[j].name == gname)
            {
                env.tensors[j].require_grad=true; // record grad_to info.
            }
        }
    }
}