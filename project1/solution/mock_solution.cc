#include "mock_solution.h"
#include "hw2c.tab.c"
#include "lex.yy.c"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>

extern RootNode * root;

int main() {

    Json::Reader reader;
    Json::Value cases;
 
    // Env env_example;
    // RootNode root_example;
    // string path_example;
    // path_example = "./kernels/"+env_example.name+".cc";
    // mock_env_example(env_example);
    // mock_root_example(root_example);
    // gen_and_save(path_example, env_example, root_example);

    ifstream file_example("./cases/example.json");

    if (reader.parse(file_example, cases)) {
        Env env_example;
        string path_example;
        get_env_from_json(cases, env_example);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_example);
        // check_env(env_example);
        path_example = "./kernels/"+env_example.name+".cc";
        gen_and_save(path_example, env_example, *root);
    }

    // Env env_case1;
    // RootNode root_case1;
    // string path_case1;
    // mock_env_case1(env_case1);
    // mock_root_case1(root_case1);
    // path_case1 = "./kernels/"+env_case1.name+".cc";
    // gen_and_save(path_case1, env_case1, root_case1);

    ifstream file_case1("./cases/case1.json");

    if (reader.parse(file_case1, cases)) {
        Env env_case1;
        string path_case1;
        get_env_from_json(cases, env_case1);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_case1);
        // check_env(env_case1);
        path_case1 = "./kernels/"+env_case1.name+".cc";
        gen_and_save(path_case1, env_case1, *root);
    }

    // Env env_case4;
    // string path_case4;
    // mock_env_case4(env_case4);
    // yy_switch_to_buffer(yy_scan_string("A<16, 32>[i, j] = A<16, 32>[i, j] + B<16, 32>[i, k] * C<32, 32>[k, j];"));
    // yyparse(&env_case4);
    // path_case4 = "./kernels/"+env_case4.name+".cc";
    // gen_and_save(path_case4, env_case4, *root);

    ifstream file_case4("./cases/case4.json");
    
    if (reader.parse(file_case4, cases)) {
        Env env_case4;
        string path_case4;
        get_env_from_json(cases, env_case4);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_case4);
        // check_env(env_case4);
        path_case4 = "./kernels/"+env_case4.name+".cc";
        gen_and_save(path_case4, env_case4, *root);
    }

    // Env env_case5;
    // RootNode root_case5;
    // string path_case5;
    // mock_env_case5(env_case5);
    // mock_root_case5(root_case5);
    // path_case5 = "./kernels/"+env_case5.name+".cc";
    // gen_and_save(path_case5, env_case5, root_case5);

    ifstream file_case5("./cases/case5.json");
    
    if (reader.parse(file_case5, cases)) {
        Env env_case5;
        string path_case5;
        get_env_from_json(cases, env_case5);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_case5);
        // check_env(env_case5);
        path_case5 = "./kernels/"+env_case5.name+".cc";
        gen_and_save(path_case5, env_case5, *root);
    }
    
    // Env env_case6;
    // RootNode root_case6;
    // string path_case6;
    // mock_env_case6(env_case6);
    // mock_root_case6(root_case6);
    // path_case6 = "./kernels/"+env_case6.name+".cc";
    // gen_and_save(path_case6, env_case6, root_case6);

    ifstream file_case6("./cases/case6.json");
    
    if (reader.parse(file_case6, cases)) {
        Env env_case6;
        string path_case6;
        get_env_from_json(cases, env_case6);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_case6);
        // check_env(env_case6);
        path_case6 = "./kernels/"+env_case6.name+".cc";
        gen_and_save(path_case6, env_case6, *root);
    }

    // Env env_case7;
    // RootNode root_case7;
    // string path_case7;
    // mock_env_case7(env_case7);
    // mock_root_case7(root_case7);
    // path_case7 = "./kernels/"+env_case7.name+".cc";
    // gen_and_save(path_case7, env_case7, root_case7);

    ifstream file_case7("./cases/case7.json");
    
    if (reader.parse(file_case7, cases)) {
        Env env_case7;
        string path_case7;
        get_env_from_json(cases, env_case7);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_case7);
        // check_env(env_case7);
        path_case7 = "./kernels/"+env_case7.name+".cc";
        gen_and_save(path_case7, env_case7, *root);
    }
    
    // Env env_case10;
    // RootNode root_case10;
    // string path_case10;
    // mock_env_case10(env_case10);
    // mock_root_case10(root_case10);
    // path_case10 = "./kernels/"+env_case10.name+".cc";
    // gen_and_save(path_case10, env_case10, root_case10);
    // return 0;

    ifstream file_case10("./cases/case10.json");
    
    if (reader.parse(file_case10, cases)) {
        Env env_case10;
        string path_case10;
        get_env_from_json(cases, env_case10);
        yy_switch_to_buffer(yy_scan_string(cases["kernel"].asString().c_str()));
        yyparse(&env_case10);
        // check_env(env_case10);
        path_case10 = "./kernels/"+env_case10.name+".cc";
        gen_and_save(path_case10, env_case10, *root);
    }
}

void get_env_from_json(Json::Value value, Env & env) 
{
    env.name = value["name"].asString();
    if (value["data_type"].asString() == "float") 
    {
        env.isInt = false;
    }
    else env.isInt = true;

    for (int i = 0; i < value["ins"].size(); ++i)
    {
        Tensor t;
        t.name = value["ins"][i].asString();
        env.tensors.push_back(t);
    }

    for (int i = 0; i < value["outs"].size(); ++i)
    {
        Tensor t;
        t.name = value["outs"][i].asString();
        env.tensors.push_back(t);
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

void mock_env_example(Env& env) {
    env.name = "kernel_example";
    env.isInt = false;

    vector<int> shape;
    shape.push_back(32);
    shape.push_back(16);
    Tensor a,b,c;
    a.name = "A";
    a.shape = shape;
    b.name = "B";
    b.shape = shape;
    c.name = "C";
    c.shape = shape;
    env.tensors.push_back(b);
    env.tensors.push_back(c);
    env.tensors.push_back(a);
}

void mock_root_example(RootNode& root){
    StmtNode* stmtNode = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode = new RHSNode();
    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    i->variableIndices.push_back(0);
    i->expr = "i";
    j->variableIndices.push_back(1);
    j->expr = "j";

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 2; // A
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(32);
    lhsNode->tRefNode->cListNode->shape.push_back(16);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode->tRefNode->aListNode->idExprList.push_back(j);
    
    // 构造右部
    rhsNode->type = RHSType::binary;
    rhsNode->op = Operation::times;

    RHSNode* node1 = new RHSNode();
    RHSNode* node2 = new RHSNode();
    node1->type = RHSType::tref;
    node2->type = RHSType::tref;
    node1->tRefNode = new TRefNode();
    node1->tRefNode->paramterIndex = 1;  // C
    node1->tRefNode->cListNode = new CListNode();
    node1->tRefNode->cListNode->shape.push_back(32);
    node1->tRefNode->cListNode->shape.push_back(16);
    node1->tRefNode->aListNode = new AListNode();
    node1->tRefNode->aListNode->idExprList.push_back(i);
    node1->tRefNode->aListNode->idExprList.push_back(j);
    node2->tRefNode = new TRefNode();
    node2->tRefNode->paramterIndex = 0;  // B
    node2->tRefNode->cListNode = new CListNode();
    node2->tRefNode->cListNode->shape.push_back(32);
    node2->tRefNode->cListNode->shape.push_back(16);
    node2->tRefNode->aListNode = new AListNode();
    node2->tRefNode->aListNode->idExprList.push_back(i);
    node2->tRefNode->aListNode->idExprList.push_back(j);

    rhsNode->lnode = node1;
    rhsNode->rnode = node2;

    Variable vi, vj;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 32;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 16;
    stmtNode->variables.push_back(vi);
    stmtNode->variables.push_back(vj);

    stmtNode->lhsNode = lhsNode;
    stmtNode->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode);
}

void mock_env_case1(Env& env) {
    env.name = "kernel_case1";
    env.isInt = false;

    vector<int> shape;
    shape.push_back(32);
    shape.push_back(16);
    Tensor a;
    a.name = "A";
    a.shape = shape;
    env.tensors.push_back(a);
}

void mock_root_case1(RootNode& root){
    StmtNode* stmtNode = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode = new RHSNode();
    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    i->variableIndices.push_back(0);
    i->expr = "i";
    j->variableIndices.push_back(1);
    j->expr = "j";

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 0; // A
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(32);
    lhsNode->tRefNode->cListNode->shape.push_back(16);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode->tRefNode->aListNode->idExprList.push_back(j);

    // 构造右部
    rhsNode->type = RHSType::constref;
    rhsNode->constNode = new ConstNode();
    rhsNode->constNode->isInt = true;
    rhsNode->constNode->intVal = 2;

    Variable vi, vj;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 32;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 16;
    stmtNode->variables.push_back(vi);
    stmtNode->variables.push_back(vj);

    stmtNode->lhsNode = lhsNode;
    stmtNode->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode);
}

void mock_env_case4(Env& env) {
    env.name = "kernel_case4";
    env.isInt = false;

    vector<int> shape1632, shape3232;
    shape1632.push_back(16);
    shape1632.push_back(32);
    shape3232.push_back(32);
    shape3232.push_back(32);
    Tensor a,b,c;
    a.name = "A";
    a.shape = shape1632;
    b.name = "B";
    b.shape = shape1632;
    c.name = "C";
    c.shape = shape3232;
    env.tensors.push_back(b);
    env.tensors.push_back(c);
    env.tensors.push_back(a);
}

void mock_root_case4(RootNode& root){
    StmtNode* stmtNode = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode = new RHSNode();
    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    IdExprNode *k = new IdExprNode();
    i->variableIndices.push_back(0);
    i->expr = "i";
    j->variableIndices.push_back(1);
    j->expr = "j";
    k->variableIndices.push_back(2);
    k->expr = "k";

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 2; // A
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(16);
    lhsNode->tRefNode->cListNode->shape.push_back(32);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode->tRefNode->aListNode->idExprList.push_back(j);

    // 构造右部
    rhsNode->type = RHSType::binary;
    rhsNode->op = Operation::plus;

    RHSNode* node1 = new RHSNode(); // A<16, 32>[i, j]
    node1->type = RHSType::tref;
    node1->tRefNode = new TRefNode();
    node1->tRefNode->paramterIndex = 2; // A
    node1->tRefNode->cListNode = new CListNode();
    node1->tRefNode->cListNode->shape.push_back(16);
    node1->tRefNode->cListNode->shape.push_back(32);
    node1->tRefNode->aListNode = new AListNode();
    node1->tRefNode->aListNode->idExprList.push_back(i);
    node1->tRefNode->aListNode->idExprList.push_back(j);


    RHSNode* node2 = new RHSNode();
    node2->type = RHSType::binary;
    node2->op = Operation::times;
    RHSNode* node3 = new RHSNode(); // B<16, 32>[i, k]
    RHSNode* node4 = new RHSNode(); // C<32, 32>[k, j]
    node3->type = RHSType::tref;
    node3->tRefNode = new TRefNode();
    node3->tRefNode->paramterIndex = 0; // B
    node3->tRefNode->cListNode = new CListNode();
    node3->tRefNode->cListNode->shape.push_back(16);
    node3->tRefNode->cListNode->shape.push_back(32);
    node3->tRefNode->aListNode = new AListNode();
    node3->tRefNode->aListNode->idExprList.push_back(i);
    node3->tRefNode->aListNode->idExprList.push_back(k);
    node4->type = RHSType::tref;
    node4->tRefNode = new TRefNode();
    node4->tRefNode->paramterIndex = 1; // C
    node4->tRefNode->cListNode = new CListNode();
    node4->tRefNode->cListNode->shape.push_back(32);
    node4->tRefNode->cListNode->shape.push_back(32);
    node4->tRefNode->aListNode = new AListNode();
    node4->tRefNode->aListNode->idExprList.push_back(k);
    node4->tRefNode->aListNode->idExprList.push_back(j);

    node2->lnode = node3;
    node2->rnode = node4;

    rhsNode->lnode = node1;
    rhsNode->rnode = node2;

    Variable vi, vj, vk;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 16;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 32;
    vk.name = "k";
    vk.lowerBound = 0;
    vk.upperBound = 32;
    stmtNode->variables.push_back(vi);
    stmtNode->variables.push_back(vj);
    stmtNode->variables.push_back(vk);

    stmtNode->lhsNode = lhsNode;
    stmtNode->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode);
}

void mock_env_case5(Env& env) {
    env.name = "kernel_case5";
    env.isInt = false;

    vector<int> shape1632, shape3232, shape1;
    shape1632.push_back(16);
    shape1632.push_back(32);
    shape3232.push_back(32);
    shape3232.push_back(32);
    shape1.push_back(1);
    Tensor a,b,c,d, alpha, beta;
    a.name = "A";
    a.shape = shape1632;
    b.name = "B";
    b.shape = shape1632;
    c.name = "C";
    c.shape = shape3232;
    d.name = "D";
    d.shape = shape1632;
    alpha.name = "alpha";
    alpha.shape = shape1;
    beta.name = "beta";
    beta.shape = shape1;
    env.tensors.push_back(b);
    env.tensors.push_back(c);
    env.tensors.push_back(d);
    env.tensors.push_back(alpha);
    env.tensors.push_back(beta);
    env.tensors.push_back(a);
}

void mock_root_case5(RootNode& root){
    StmtNode* stmtNode1 = new StmtNode();
    StmtNode* stmtNode2 = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode1 = new RHSNode();
    RHSNode* rhsNode2 = new RHSNode();
    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    IdExprNode *k = new IdExprNode();
    i->variableIndices.push_back(0);
    i->expr = "i";
    j->variableIndices.push_back(1);
    j->expr = "j";
    k->variableIndices.push_back(2);
    k->expr = "k";

    // stmtNode1
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 5; // A
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(16);
    lhsNode->tRefNode->cListNode->shape.push_back(32);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode->tRefNode->aListNode->idExprList.push_back(j);

    rhsNode1->type = RHSType::binary;
    rhsNode1->op = Operation::plus;

    RHSNode* node1 = new RHSNode(); // A<16, 32>[i, j]
    node1->type = RHSType::tref;
    node1->tRefNode = new TRefNode();
    node1->tRefNode->paramterIndex = 5; // A
    node1->tRefNode->cListNode = new CListNode();
    node1->tRefNode->cListNode->shape.push_back(16);
    node1->tRefNode->cListNode->shape.push_back(32);
    node1->tRefNode->aListNode = new AListNode();
    node1->tRefNode->aListNode->idExprList.push_back(i);
    node1->tRefNode->aListNode->idExprList.push_back(j);

    RHSNode* node2 = new RHSNode(); // alpha<1> * (B<16, 32>[i, k] * C<32, 32>[k, j])
    RHSNode* node3 = new RHSNode(); // alpha<1>
    RHSNode* node4 = new RHSNode(); // (B<16, 32>[i, k] * C<32, 32>[k, j])
    RHSNode* node5 = new RHSNode(); // B<16, 32>[i, k] * C<32, 32>[k, j]
    RHSNode* node6 = new RHSNode(); // B<16, 32>[i, k]
    RHSNode* node7 = new RHSNode(); // C<32, 32>[k, j]

    node2->type = RHSType::binary;
    node2->op = Operation::times;

    node3->type = RHSType::sref;
    node3->sRefNode = new SRefNode();
    node3->sRefNode->paramterIndex = 3; // alpha
    node3->sRefNode->cListNode = new CListNode();
    node3->sRefNode->cListNode->shape.push_back(1);
    
    node4->type = RHSType::uniary;

    node5->type = RHSType::binary;
    node5->op = Operation::times;

    node6->type = RHSType::tref;
    node6->tRefNode = new TRefNode();
    node6->tRefNode->paramterIndex = 0; // B
    node6->tRefNode->cListNode = new CListNode();
    node6->tRefNode->cListNode->shape.push_back(16);
    node6->tRefNode->cListNode->shape.push_back(32);
    node6->tRefNode->aListNode = new AListNode();
    node6->tRefNode->aListNode->idExprList.push_back(i);
    node6->tRefNode->aListNode->idExprList.push_back(k);

    node7->type = RHSType::tref;
    node7->tRefNode = new TRefNode();
    node7->tRefNode->paramterIndex = 1; // C
    node7->tRefNode->cListNode = new CListNode();
    node7->tRefNode->cListNode->shape.push_back(32);
    node7->tRefNode->cListNode->shape.push_back(32);
    node7->tRefNode->aListNode = new AListNode();
    node7->tRefNode->aListNode->idExprList.push_back(k);
    node7->tRefNode->aListNode->idExprList.push_back(j);

    node5->lnode = node6;
    node5->rnode = node7;
    node4->lnode = node5;
    node2->lnode = node3;
    node2->rnode = node4;
    rhsNode1->lnode = node1;
    rhsNode1->rnode = node2;

    Variable vi, vj, vk;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 16;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 32;
    vk.name = "k";
    vk.lowerBound = 0;
    vk.upperBound = 32;
    stmtNode1->variables.push_back(vi);
    stmtNode1->variables.push_back(vj);
    stmtNode1->variables.push_back(vk);

    stmtNode1->lhsNode = lhsNode;
    stmtNode1->rhsNode = rhsNode1;

    // stmtNode2
    rhsNode2->type = RHSType::binary; // A<16, 32>[i, j] + beta<1> * D<16, 32>[i, j]
    rhsNode2->op = Operation::plus;

    RHSNode* node8 = new RHSNode(); // A<16, 32>[i, j]
    RHSNode* node9 = new RHSNode(); // beta<1> * D<16, 32>[i, j]
    RHSNode* node10 = new RHSNode(); // beta<1>
    RHSNode* node11 = new RHSNode(); // D<16, 32>[i, j]

    node8->type = RHSType::tref;
    node8->tRefNode = new TRefNode();
    node8->tRefNode->paramterIndex = 5; // A
    node8->tRefNode->cListNode = new CListNode();
    node8->tRefNode->cListNode->shape.push_back(16);
    node8->tRefNode->cListNode->shape.push_back(32);
    node8->tRefNode->aListNode = new AListNode();
    node8->tRefNode->aListNode->idExprList.push_back(i);
    node8->tRefNode->aListNode->idExprList.push_back(j);
    
    node9->type = RHSType::binary;
    node9->op = Operation::times;

    node10->type = RHSType::sref; // beta
    node10->sRefNode = new SRefNode();
    node10->sRefNode->paramterIndex = 4; // alpha
    node10->sRefNode->cListNode = new CListNode();
    node10->sRefNode->cListNode->shape.push_back(1);

    node11->type = RHSType::tref; // D
    node11->tRefNode = new TRefNode();
    node11->tRefNode->paramterIndex = 2;
    node11->tRefNode->cListNode = new CListNode();
    node11->tRefNode->cListNode->shape.push_back(16);
    node11->tRefNode->cListNode->shape.push_back(32);
    node11->tRefNode->aListNode = new AListNode();
    node11->tRefNode->aListNode->idExprList.push_back(i);
    node11->tRefNode->aListNode->idExprList.push_back(j);

    node9->lnode = node10;
    node9->rnode = node11;
    rhsNode2->lnode = node8;
    rhsNode2->rnode = node9;

    stmtNode2->variables.push_back(vi);
    stmtNode2->variables.push_back(vj);

    stmtNode2->lhsNode = lhsNode;
    stmtNode2->rhsNode = rhsNode2;

    root.stmtNodes.push_back(stmtNode1);
    root.stmtNodes.push_back(stmtNode2);
}

void mock_env_case6(Env& env) {
    env.name = "kernel_case6";
    env.isInt = false;

    Tensor a,b,c;
    a.name = "A";
    a.shape.push_back(2);
    a.shape.push_back(8);
    a.shape.push_back(5);
    a.shape.push_back(5);
    b.name = "B";
    b.shape.push_back(2);
    b.shape.push_back(16);
    b.shape.push_back(7);
    b.shape.push_back(7);
    c.name = "C";
    c.shape.push_back(8);
    c.shape.push_back(16);
    c.shape.push_back(3);
    c.shape.push_back(3);
    env.tensors.push_back(b);
    env.tensors.push_back(c);
    env.tensors.push_back(a);
}

void mock_root_case6(RootNode& root){
    StmtNode* stmtNode = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode = new RHSNode();
    IdExprNode *en, *ek, *ep, *eq, *ec, *er, *es, *epr, *eqs;
    en = new IdExprNode();
    ek = new IdExprNode();
    ep = new IdExprNode();
    eq = new IdExprNode();
    ec = new IdExprNode();
    er = new IdExprNode();
    es = new IdExprNode();
    epr = new IdExprNode();
    eqs = new IdExprNode();
    en->expr = "n"; en->variableIndices.push_back(0);
    ek->expr = "k"; ek->variableIndices.push_back(1);
    ep->expr = "p"; ep->variableIndices.push_back(2);
    eq->expr = "q"; eq->variableIndices.push_back(3);
    ec->expr = "c"; ec->variableIndices.push_back(4);
    er->expr = "r"; er->variableIndices.push_back(5);
    es->expr = "s"; es->variableIndices.push_back(6);
    epr->expr = "p + r"; epr->variableIndices.push_back(2); epr->variableIndices.push_back(5);
    eqs->expr = "q + s"; eqs->variableIndices.push_back(3); eqs->variableIndices.push_back(6);

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 2; // A
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(2);
    lhsNode->tRefNode->cListNode->shape.push_back(8);
    lhsNode->tRefNode->cListNode->shape.push_back(5);
    lhsNode->tRefNode->cListNode->shape.push_back(5);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(en);
    lhsNode->tRefNode->aListNode->idExprList.push_back(ek);
    lhsNode->tRefNode->aListNode->idExprList.push_back(ep);
    lhsNode->tRefNode->aListNode->idExprList.push_back(eq);

    // 构造右部
    rhsNode->type = RHSType::binary;
    rhsNode->op = Operation::plus;

    RHSNode* node1 = new RHSNode(); // A<2, 8, 5, 5>[n, k, p, q]
    node1->type = RHSType::tref;
    node1->tRefNode = new TRefNode();
    node1->tRefNode->paramterIndex = 2; // A
    node1->tRefNode->cListNode = new CListNode();
    node1->tRefNode->cListNode->shape.push_back(2);
    node1->tRefNode->cListNode->shape.push_back(8);
    node1->tRefNode->cListNode->shape.push_back(5);
    node1->tRefNode->cListNode->shape.push_back(5);
    node1->tRefNode->aListNode = new AListNode();
    node1->tRefNode->aListNode->idExprList.push_back(en);
    node1->tRefNode->aListNode->idExprList.push_back(ek);
    node1->tRefNode->aListNode->idExprList.push_back(ep);
    node1->tRefNode->aListNode->idExprList.push_back(eq);

    RHSNode* node2 = new RHSNode();
    node2->type = RHSType::binary;
    node2->op = Operation::times;
    RHSNode* node3 = new RHSNode(); // B<2, 16, 7, 7>[n, c, p + r, q + s]
    RHSNode* node4 = new RHSNode(); // C<8, 16, 3, 3>[k, c, r, s]
    node3->type = RHSType::tref;
    node3->tRefNode = new TRefNode();
    node3->tRefNode->paramterIndex = 0; // B
    node3->tRefNode->cListNode = new CListNode();
    node3->tRefNode->cListNode->shape.push_back(2);
    node3->tRefNode->cListNode->shape.push_back(16);
    node3->tRefNode->cListNode->shape.push_back(7);
    node3->tRefNode->cListNode->shape.push_back(7);
    node3->tRefNode->aListNode = new AListNode();
    node3->tRefNode->aListNode->idExprList.push_back(en);
    node3->tRefNode->aListNode->idExprList.push_back(ec);
    node3->tRefNode->aListNode->idExprList.push_back(epr);
    node3->tRefNode->aListNode->idExprList.push_back(eqs);
    node4->type = RHSType::tref;
    node4->tRefNode = new TRefNode();
    node4->tRefNode->paramterIndex = 1; // C
    node4->tRefNode->cListNode = new CListNode();
    node4->tRefNode->cListNode->shape.push_back(8);
    node4->tRefNode->cListNode->shape.push_back(16);
    node4->tRefNode->cListNode->shape.push_back(3);
    node4->tRefNode->cListNode->shape.push_back(3);
    node4->tRefNode->aListNode = new AListNode();
    node4->tRefNode->aListNode->idExprList.push_back(ek);
    node4->tRefNode->aListNode->idExprList.push_back(ec);
    node4->tRefNode->aListNode->idExprList.push_back(er);
    node4->tRefNode->aListNode->idExprList.push_back(es);

    node2->lnode = node3;
    node2->rnode = node4;

    rhsNode->lnode = node1;
    rhsNode->rnode = node2;

    Variable vn, vk, vp, vq, vc, vr, vs;
    vn.name="n"; vk.name="k"; vp.name="p"; vq.name="q"; vc.name="c"; vr.name="r"; vs.name="s";
    vn.lowerBound = 0; vk.lowerBound = 0; vp.lowerBound = 0; vq.lowerBound = 0;
    vc.lowerBound = 0; vr.lowerBound = 0; vs.lowerBound = 0;
    vn.upperBound = 2; vk.upperBound = 8; vp.upperBound = 5; vq.upperBound = 5;
    vc.upperBound = 16; vr.upperBound = 3; vs.upperBound = 3;
    stmtNode->variables.push_back(vn);
    stmtNode->variables.push_back(vk);
    stmtNode->variables.push_back(vp);
    stmtNode->variables.push_back(vq);
    stmtNode->variables.push_back(vc);
    stmtNode->variables.push_back(vr);
    stmtNode->variables.push_back(vs);

    stmtNode->lhsNode = lhsNode;
    stmtNode->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode);
}

void mock_env_case7(Env& env) {
    env.name = "kernel_case7";
    env.isInt = false;

    Tensor a,b;
    a.name = "A";
    a.shape.push_back(32);
    a.shape.push_back(16);
    b.name = "B";
    b.shape.push_back(16);
    b.shape.push_back(32);
    env.tensors.push_back(a);
    env.tensors.push_back(b);
}

void mock_root_case7(RootNode& root){
    StmtNode* stmtNode = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode = new RHSNode();
    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    i->variableIndices.push_back(0);
    i->expr = "i";
    j->variableIndices.push_back(1);
    j->expr = "j";

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 1; // B
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(16);
    lhsNode->tRefNode->cListNode->shape.push_back(32);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode->tRefNode->aListNode->idExprList.push_back(j);

    // 构造右部
    rhsNode->type = RHSType::tref;
    rhsNode->tRefNode = new TRefNode();
    rhsNode->tRefNode->paramterIndex = 0;  // A
    rhsNode->tRefNode->cListNode = new CListNode();
    rhsNode->tRefNode->cListNode->shape.push_back(32);
    rhsNode->tRefNode->cListNode->shape.push_back(16);
    rhsNode->tRefNode->aListNode = new AListNode();
    rhsNode->tRefNode->aListNode->idExprList.push_back(j);
    rhsNode->tRefNode->aListNode->idExprList.push_back(i);

    Variable vi, vj;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 16;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 32;
    stmtNode->variables.push_back(vi);
    stmtNode->variables.push_back(vj);

    stmtNode->lhsNode = lhsNode;
    stmtNode->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode);
}

void mock_env_case10(Env& env) {
    env.name = "kernel_case10";
    env.isInt = false;

    Tensor a,b;
    a.name = "A";
    a.shape.push_back(8);
    a.shape.push_back(8);
    b.name = "B";
    b.shape.push_back(10);
    b.shape.push_back(10);
    env.tensors.push_back(b);
    env.tensors.push_back(a);
}

void mock_root_case10(RootNode& root){
    StmtNode* stmtNode = new StmtNode();
    LHSNode* lhsNode = new LHSNode();
    RHSNode* rhsNode = new RHSNode();
    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    IdExprNode *i1 = new IdExprNode();
    IdExprNode *i2 = new IdExprNode();
    i->variableIndices.push_back(0);
    i->expr = "i";
    j->variableIndices.push_back(1);
    j->expr = "j";
    i1->variableIndices.push_back(0);
    i1->expr = "i + 1";
    i2->variableIndices.push_back(0);
    i2->expr = "i + 2";

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 1; // A
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(8);
    lhsNode->tRefNode->cListNode->shape.push_back(8);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode->tRefNode->aListNode->idExprList.push_back(j);

    // 构造右部
    rhsNode->type = RHSType::binary;
    rhsNode->op = Operation::divide;

    RHSNode* node1 = new RHSNode(); // (B<10, 10>[i, j] + B<10, 10>[i + 1, j] + B<10, 10>[i + 2, j])
    RHSNode* node2 = new RHSNode(); // B<10, 10>[i, j] + B<10, 10>[i + 1, j] + B<10, 10>[i + 2, j]
    RHSNode* node3 = new RHSNode(); // B<10, 10>[i, j]
    RHSNode* node4 = new RHSNode(); // B<10, 10>[i + 1, j] + B<10, 10>[i + 2, j]
    RHSNode* node5 = new RHSNode(); // B<10, 10>[i + 1, j]
    RHSNode* node6 = new RHSNode(); // B<10, 10>[i + 2, j]
    RHSNode* node7 = new RHSNode(); // const 3

    node1->type = RHSType::uniary;

    node2->type = RHSType::binary;
    node2->op = Operation::plus;

    node3->type = RHSType::tref;
    node3->tRefNode = new TRefNode();
    node3->tRefNode->paramterIndex = 0; // B
    node3->tRefNode->cListNode = new CListNode();
    node3->tRefNode->cListNode->shape.push_back(8);
    node3->tRefNode->cListNode->shape.push_back(8);
    node3->tRefNode->aListNode = new AListNode();
    node3->tRefNode->aListNode->idExprList.push_back(i);
    node3->tRefNode->aListNode->idExprList.push_back(j);

    node4->type = RHSType::binary;
    node4->op = Operation::plus;

    node5->type = RHSType::tref;
    node5->tRefNode = new TRefNode();
    node5->tRefNode->paramterIndex = 0;
    node5->tRefNode->cListNode = new CListNode();
    node5->tRefNode->cListNode->shape.push_back(8);
    node5->tRefNode->cListNode->shape.push_back(8);
    node5->tRefNode->aListNode = new AListNode();
    node5->tRefNode->aListNode->idExprList.push_back(i1);
    node5->tRefNode->aListNode->idExprList.push_back(j);

    node6->type = RHSType::tref;
    node6->tRefNode = new TRefNode();
    node6->tRefNode->paramterIndex = 0;
    node6->tRefNode->cListNode = new CListNode();
    node6->tRefNode->cListNode->shape.push_back(8);
    node6->tRefNode->cListNode->shape.push_back(8);
    node6->tRefNode->aListNode = new AListNode();
    node6->tRefNode->aListNode->idExprList.push_back(i2);
    node6->tRefNode->aListNode->idExprList.push_back(j);

    node7->type = RHSType::constref;
    node7->constNode = new ConstNode();
    node7->constNode->isInt = true;
    node7->constNode->intVal = 3;

    node4->lnode = node5;
    node4->rnode = node6;
    node2->lnode = node3;
    node2->rnode = node4;
    node1->lnode = node2;
    rhsNode->lnode = node1;
    rhsNode->rnode = node7;

    Variable vi, vj;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 8;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 8;
    stmtNode->variables.push_back(vi);
    stmtNode->variables.push_back(vj);

    stmtNode->lhsNode = lhsNode;
    stmtNode->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode);
}