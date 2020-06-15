#include "mock_replace_index.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void mock_replace_index_main() {    
    Env env_case6;
    RootNode root_case6;
    string path_case6;
    mock_replace_index_env_case6(env_case6);
    mock_replace_index_root_case6(root_case6);
    path_case6 = "./kernels/"+env_case6.name+".cc";
    replace_check(env_case6, root_case6);
    // cout << "--------AFTER REPLACEMENT ----------" << endl;
    // cout << "[0]" << endl;
    // cout << "indexToReplace:\t" << root_case6.stmtNodes[0]->replacements[0].indexToReplace << endl;
    // cout << "subtitute.name:\t" << root_case6.stmtNodes[0]->replacements[0].subtitute.name << endl;
    // cout << "subtitute.lowerBound:\t" << root_case6.stmtNodes[0]->replacements[0].subtitute.lowerBound << endl;
    // cout << "subtitute.upperBound:\t" << root_case6.stmtNodes[0]->replacements[0].subtitute.upperBound << endl;
    // cout << "withConst:\t" << root_case6.stmtNodes[0]->replacements[0].withConst << endl;
    // cout << "withConstVal:\t" << root_case6.stmtNodes[0]->replacements[0].withConstVal << endl;
    // cout << "withVariableIndex:\t" << root_case6.stmtNodes[0]->replacements[0].withVariableIndex << endl;

    // cout << "[1]" << endl;
    // cout << "indexToReplace:\t" << root_case6.stmtNodes[0]->replacements[1].indexToReplace << endl;
    // cout << "subtitute.name:\t" << root_case6.stmtNodes[0]->replacements[1].subtitute.name << endl;
    // cout << "subtitute.lowerBound:\t" << root_case6.stmtNodes[0]->replacements[1].subtitute.lowerBound << endl;
    // cout << "subtitute.upperBound:\t" << root_case6.stmtNodes[0]->replacements[1].subtitute.upperBound << endl;
    // cout << "withConst:\t" << root_case6.stmtNodes[0]->replacements[1].withConst << endl;
    // cout << "withConstVal:\t" << root_case6.stmtNodes[0]->replacements[1].withConstVal << endl;
    // cout << "withVariableIndex:\t" << root_case6.stmtNodes[0]->replacements[1].withVariableIndex << endl;
    gen_and_save(path_case6, env_case6, root_case6);
    
    Env env_case10;
    RootNode root_case10;
    string path_case10;
    mock_replace_index_env_case10(env_case10);
    mock_replace_index_root_case10(root_case10);
    path_case10 = "./kernels/"+env_case10.name+".cc";
    replace_check(env_case10, root_case10);
    gen_and_save(path_case10, env_case10, root_case10);
}

void mock_replace_index_env_case6(Env& env) {
    env.name = "grad_case6";
    env.isInt = false;

    // dB[n][c][p+r][q+s] =  dA[n, k, p, q] * C[k, c, r, s]

    Tensor da, db, c;
    da.name = "dA";
    da.shape.push_back(2);
    da.shape.push_back(8);
    da.shape.push_back(5);
    da.shape.push_back(5);
    db.name = "dB";
    db.shape.push_back(2);
    db.shape.push_back(16);
    db.shape.push_back(7);
    db.shape.push_back(7);
    c.name = "C";
    c.shape.push_back(8);
    c.shape.push_back(16);
    c.shape.push_back(3);
    c.shape.push_back(3);
    env.tensors.push_back(c);
    env.tensors.push_back(da);
    env.tensors.push_back(db);
}

void mock_replace_index_root_case6(RootNode& root){
    // dB[n][c][p+r][q+s] =  dA[n, k, p, q] * C[k, c, r, s]

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
    en->expr = "n"; en->ids.push_back("n");
    ek->expr = "k"; ek->ids.push_back("k");
    ep->expr = "p"; ep->ids.push_back("p");
    eq->expr = "q"; eq->ids.push_back("q");
    ec->expr = "c"; ec->ids.push_back("c");
    er->expr = "r"; er->ids.push_back("r");
    es->expr = "s"; es->ids.push_back("s");
    epr->expr = "p + r"; epr->ids.push_back("p"); epr->ids.push_back("r"); epr->op.push_back(Operation::plus);
    eqs->expr = "q + s"; eqs->ids.push_back("q"); eqs->ids.push_back("s"); eqs->op.push_back(Operation::plus);

    // 构造左部
    lhsNode->tRefNode = new TRefNode();
    lhsNode->tRefNode->paramterIndex = 2; // dB
    lhsNode->tRefNode->cListNode = new CListNode();
    lhsNode->tRefNode->cListNode->shape.push_back(2);
    lhsNode->tRefNode->cListNode->shape.push_back(16);
    lhsNode->tRefNode->cListNode->shape.push_back(7);
    lhsNode->tRefNode->cListNode->shape.push_back(7);
    lhsNode->tRefNode->aListNode = new AListNode();
    lhsNode->tRefNode->aListNode->idExprList.push_back(en);
    lhsNode->tRefNode->aListNode->idExprList.push_back(ec);
    lhsNode->tRefNode->aListNode->idExprList.push_back(epr);
    lhsNode->tRefNode->aListNode->idExprList.push_back(eqs);

    // 构造右部
    rhsNode->type = RHSType::binary;
    rhsNode->op = Operation::times;

    RHSNode* node1 = new RHSNode(); // dA[n, k, p, q] 
    node1->type = RHSType::tref;
    node1->tRefNode = new TRefNode();
    node1->tRefNode->paramterIndex = 1; // dA
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
    node2->type = RHSType::tref; // C<8, 16, 3, 3>[k, c, r, s]
    node2->tRefNode = new TRefNode();
    node2->tRefNode->paramterIndex = 0; // C
    node2->tRefNode->cListNode = new CListNode();
    node2->tRefNode->cListNode->shape.push_back(8);
    node2->tRefNode->cListNode->shape.push_back(16);
    node2->tRefNode->cListNode->shape.push_back(3);
    node2->tRefNode->cListNode->shape.push_back(3);
    node2->tRefNode->aListNode = new AListNode();
    node2->tRefNode->aListNode->idExprList.push_back(ek);
    node2->tRefNode->aListNode->idExprList.push_back(ec);
    node2->tRefNode->aListNode->idExprList.push_back(er);
    node2->tRefNode->aListNode->idExprList.push_back(es);

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

void mock_replace_index_env_case10(Env& env) {
    env.name = "grad_case10";
    env.isInt = false;

    Tensor da,db;
    da.name = "dA";
    da.shape.push_back(8);
    da.shape.push_back(8);
    db.name = "dB";
    db.shape.push_back(10);
    db.shape.push_back(8);
    env.tensors.push_back(da);
    env.tensors.push_back(db);
}

void mock_replace_index_root_case10(RootNode& root){
    StmtNode* stmtNode1 = new StmtNode();
    StmtNode* stmtNode2= new StmtNode();
    StmtNode* stmtNode3 = new StmtNode();

    LHSNode* lhsNode1 = new LHSNode();
    LHSNode* lhsNode2 = new LHSNode();
    LHSNode* lhsNode3 = new LHSNode();
    RHSNode* rhsNode = new RHSNode(); // 共用1个

    IdExprNode *i = new IdExprNode();
    IdExprNode *j = new IdExprNode();
    IdExprNode *i1 = new IdExprNode();
    IdExprNode *i2 = new IdExprNode();
    
    i->ids.push_back("i");
    j->ids.push_back("j");
    i1->ids.push_back("i"); i1->op.push_back(Operation::plus); i1->num.push_back(1);
    i2->ids.push_back("i"); i2->op.push_back(Operation::plus); i2->num.push_back(2);
    
    // 构造左部
    lhsNode1->tRefNode = new TRefNode();
    lhsNode1->tRefNode->paramterIndex = 1; // dB
    lhsNode1->tRefNode->cListNode = new CListNode();
    lhsNode1->tRefNode->cListNode->shape.push_back(10);
    lhsNode1->tRefNode->cListNode->shape.push_back(8);
    lhsNode1->tRefNode->aListNode = new AListNode();
    lhsNode1->tRefNode->aListNode->idExprList.push_back(i);
    lhsNode1->tRefNode->aListNode->idExprList.push_back(j);

    lhsNode2->tRefNode = new TRefNode();
    lhsNode2->tRefNode->paramterIndex = 1; // dB
    lhsNode2->tRefNode->cListNode = new CListNode();
    lhsNode2->tRefNode->cListNode->shape.push_back(10);
    lhsNode2->tRefNode->cListNode->shape.push_back(8);
    lhsNode2->tRefNode->aListNode = new AListNode();
    lhsNode2->tRefNode->aListNode->idExprList.push_back(i1);
    lhsNode2->tRefNode->aListNode->idExprList.push_back(j);

    lhsNode3->tRefNode = new TRefNode();
    lhsNode3->tRefNode->paramterIndex = 1; // dB
    lhsNode3->tRefNode->cListNode = new CListNode();
    lhsNode3->tRefNode->cListNode->shape.push_back(10);
    lhsNode3->tRefNode->cListNode->shape.push_back(8);
    lhsNode3->tRefNode->aListNode = new AListNode();
    lhsNode3->tRefNode->aListNode->idExprList.push_back(i2);
    lhsNode3->tRefNode->aListNode->idExprList.push_back(j);

    // 构造右部
    rhsNode->type = RHSType::binary;
    rhsNode->op = Operation::divide;

    RHSNode* node1 = new RHSNode(); // dA <8,8>
    RHSNode* node2 = new RHSNode(); // 3.0

    node1->type = RHSType::uniary;
    node2->type = RHSType::uniary;

    node1->type = RHSType::tref;
    node1->tRefNode = new TRefNode();
    node1->tRefNode->paramterIndex = 0; // dA
    node1->tRefNode->cListNode = new CListNode();
    node1->tRefNode->cListNode->shape.push_back(8);
    node1->tRefNode->cListNode->shape.push_back(8);
    node1->tRefNode->aListNode = new AListNode();
    node1->tRefNode->aListNode->idExprList.push_back(i);
    node1->tRefNode->aListNode->idExprList.push_back(j);

    node2->type = RHSType::constref;
    node2->constNode = new ConstNode();
    node2->constNode->isInt = true;
    node2->constNode->intVal = 3;

    rhsNode->lnode = node1;
    rhsNode->rnode = node2;

    Variable vi, vj;
    vi.name = "i";
    vi.lowerBound = 0;
    vi.upperBound = 8;
    vj.name = "j";
    vj.lowerBound = 0;
    vj.upperBound = 8;
    stmtNode1->variables.push_back(vi);
    stmtNode1->variables.push_back(vj);
    stmtNode2->variables.push_back(vi);
    stmtNode2->variables.push_back(vj);
    stmtNode3->variables.push_back(vi);
    stmtNode3->variables.push_back(vj);

    stmtNode1->lhsNode = lhsNode1;
    stmtNode1->rhsNode = rhsNode;
    stmtNode2->lhsNode = lhsNode2;
    stmtNode2->rhsNode = rhsNode;
    stmtNode3->lhsNode = lhsNode3;
    stmtNode3->rhsNode = rhsNode;
    root.stmtNodes.push_back(stmtNode1);
    root.stmtNodes.push_back(stmtNode2);
    root.stmtNodes.push_back(stmtNode3);
}