#include "backend.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string header = "#include \"../run.h\""; 
string return_type = "void";
string one_tab = "    ";

void gen_and_save(string path, Env& env, RootNode& root) {
    ostringstream oss;
    oss << header << endl << endl;
    oss << return_type << " " << env.name << gen_parameters(env) << "{" << endl;
    oss << gen_body(env, root) << "}" << endl;

    string src = oss.str();

    ofstream ofile(path, ios::out);
    ofile << src;
    ofile.close();
}

string gen_parameters(Env& env) {
    string desc = env.isInt ? "int" : "float";

    ostringstream oss;
    oss << "(";
    int size = env.tensors.size();
    for (int i = 0; i < size; i++) {
        oss << desc << " (&" << env.tensors[i].name << ")";
        vector<int> &shape = env.tensors[i].shape;
        bool isScalar = (shape.size() == 1 && shape[0] == 1);
        for (int j = 0; !isScalar && j < shape.size(); j++) {
            oss << "[" << env.tensors[i].shape[j] << "]";
        }
        if (i < size - 1) {
            oss << ", ";
        }
    }

    oss << ") ";
    return oss.str();
}

string gen_body(Env& env, RootNode& root) {
    ostringstream oss;
    
    for (int i = 0; i < root.stmtNodes.size(); i++) {
        oss << gen_loop(env, *(root.stmtNodes[i]), 0);
    }

    return oss.str();
}

string gen_loop(Env& env, StmtNode& stmt, int loop) {
    ostringstream oss;
    string indent = "";

    if (stmt.variables[loop].complex)
    {
        oss << gen_loop(env, stmt, loop + 1);
        return oss.str();
    }

    for (int i = 0; i < loop + 1; i++) {
        indent += one_tab;
    }

    string var = stmt.variables[loop].name;
    int lb = stmt.variables[loop].lowerBound;
    int ub = stmt.variables[loop].upperBound;

    // for (int i = 0; i < 32; ++i)
    oss << indent << "for (int " << var << " = " << lb << "; " << var << " < " << ub << "; ++" << var << ") {" << endl;

    if (loop < stmt.variables.size() - 1) {
        oss << gen_loop(env, stmt, loop + 1);
    } else {
        for (int i = 0; i < stmt.variables.size(); ++i)
        {
            Variable v = stmt.variables[i];
            if (v.complex)
            {
                oss << indent << one_tab;
                oss << "if " << "(" <<  v.name << " < " << v.lowerBound << " || " <<
                v.name << " >= " << v.upperBound << " ) " << " continue;\n";
            }
        }
        oss << indent << one_tab;
        oss << env.tensors[stmt.lhsNode->tRefNode->paramterIndex].name;
        vector<IdExprNode*> & lhsIdExprList = stmt.lhsNode->tRefNode->aListNode->idExprList;
        for (int i = 0; i < lhsIdExprList.size(); i++) {
            string expr = lhsIdExprList[i]->expr;
            oss << "[" << expr << "]";
        }
        oss << " = " << gen_rhs(env, *(stmt.rhsNode)) << ";" << endl;
    }
    oss << indent << "}" << endl;
    return oss.str();
}

string get_op_string(Operation op) {
    switch (op){
    case Operation::plus: return "+";
    case Operation::minus: return "-";
    case Operation::times: return "*";
    case Operation::divide: return "/";
    case Operation::mod: return "%";
    case Operation::floor_divide: return "/";
    default:return "ERROR";
    }
}

string gen_rhs(Env& env, RHSNode& rhsNode) {
    switch (rhsNode.type) {
    case RHSType::binary:
        return gen_rhs(env, *(rhsNode.lnode)) + " " + get_op_string(rhsNode.op) + " " + gen_rhs(env, *(rhsNode.rnode));
    case RHSType::uniary:
        return "(" + gen_rhs(env, *(rhsNode.lnode)) + ")";
    case RHSType::tref:
        return gen_tref(env, *(rhsNode.tRefNode));
    case RHSType::sref:
        return gen_sref(env, *(rhsNode.sRefNode));
    case RHSType::constref:
        return rhsNode.constNode->isInt ? to_string(rhsNode.constNode->intVal) : to_string(rhsNode.constNode->floatVal);
    default:
        cout << "ERROR" << endl;
        break;
    }
}

string gen_tref(Env& env, TRefNode& tRefNode) {
    ostringstream oss;
    vector<IdExprNode*> & idExprList = tRefNode.aListNode->idExprList;
    oss << env.tensors[tRefNode.paramterIndex].name;
    for (int i = 0; i < idExprList.size(); i++) {
        string expr = idExprList[i]->expr;
        oss << "[" << expr << "]";
    }
    return oss.str();
}

string gen_sref(Env& env, SRefNode& sRefNode) {
    ostringstream oss;
    oss << env.tensors[sRefNode.paramterIndex].name;
    return oss.str();
}
