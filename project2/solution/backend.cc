#include "backend.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string HEADER = "#include \"../run2.h\""; 
string RETURN_TYPE = "void";
string ONE_TAB = "    ";
vector<string> SUBTITUTE_NAMES = {"h", "w", "x", "y", "z"};

void replace_check(Env& env, RootNode& root) {
    for (int i = 0; i < root.stmtNodes.size(); i++) {
        vector<ReplacementNode>& replaceVec = root.stmtNodes[i]->replacements;
        vector<IdExprNode*>& lhsIdExprList = root.stmtNodes[i]->lhsNode->tRefNode->aListNode->idExprList;
        for (int j = 0; j < lhsIdExprList.size(); j++) {
            if (lhsIdExprList[j]->op.size() == 0) { // 单变量下标，跳过
                continue;
            }

            ReplacementNode replacement;
            // 替换下标表达式中的最后一个变量
            string varName = lhsIdExprList[j]->ids[lhsIdExprList[j]->ids.size()-1];
            for (int k = 0; k < root.stmtNodes[i]->variables.size(); k++) {
                if (varName.compare(root.stmtNodes[i]->variables[k].name) == 0) {
                    replacement.indexToReplace = k; // 找到variable表中对应变量的下标
                }
            }

            replacement.subtitute.name = SUBTITUTE_NAMES[replaceVec.size()];
            replacement.withConst = lhsIdExprList[j]->num.size() == 1;
            replacement.opWith = lhsIdExprList[j]->op[0];

            if (replacement.withConst) {
                replacement.withConstVal = lhsIdExprList[j]->num[0];
            } else {
                string withVarName = lhsIdExprList[j]->ids[0]; 
                for (int k = 0; k < root.stmtNodes[i]->variables.size(); k++) {
                    if (withVarName.compare(root.stmtNodes[i]->variables[k].name) == 0) {
                        replacement.withVariableIndex = k;
                    }
                } 
            }

            // 计算ub/lb，目前只支持表达式中有2个量 且为做加减法

            // 替代变量的范围首先由相关变量决定
            if (replacement.opWith == Operation::plus && replacement.withConst) { // x = i + 1
                replacement.subtitute.lowerBound = root.stmtNodes[i]->variables[replacement.indexToReplace].lowerBound + replacement.withConstVal;
                replacement.subtitute.upperBound = root.stmtNodes[i]->variables[replacement.indexToReplace].upperBound + replacement.withConstVal;
            } else if (replacement.opWith == Operation::minus && replacement.withConst) { // x = i - 1
                replacement.subtitute.lowerBound = root.stmtNodes[i]->variables[replacement.indexToReplace].lowerBound - replacement.withConstVal;
                replacement.subtitute.upperBound = root.stmtNodes[i]->variables[replacement.indexToReplace].upperBound - replacement.withConstVal;
            } else if (replacement.opWith == Operation::plus && !replacement.withConst) { // x = i + j
                replacement.subtitute.lowerBound = root.stmtNodes[i]->variables[replacement.indexToReplace].lowerBound + root.stmtNodes[i]->variables[replacement.withVariableIndex].lowerBound;
                replacement.subtitute.upperBound = root.stmtNodes[i]->variables[replacement.indexToReplace].upperBound + root.stmtNodes[i]->variables[replacement.withVariableIndex].upperBound;
            } else if (replacement.opWith == Operation::minus && !replacement.withConst) { // x = i - j
                replacement.subtitute.lowerBound = root.stmtNodes[i]->variables[replacement.indexToReplace].lowerBound - root.stmtNodes[i]->variables[replacement.withVariableIndex].upperBound;
                replacement.subtitute.upperBound = root.stmtNodes[i]->variables[replacement.indexToReplace].upperBound - root.stmtNodes[i]->variables[replacement.withVariableIndex].lowerBound;
            }

            // 替代变量的范围也受下标范围（张量形状）的限制
            if (replacement.subtitute.lowerBound < 0) {
                replacement.subtitute.lowerBound = 0;
            }
            if (replacement.subtitute.upperBound > root.stmtNodes[i]->lhsNode->tRefNode->cListNode->shape[j]) {
                replacement.subtitute.upperBound = root.stmtNodes[i]->lhsNode->tRefNode->cListNode->shape[j];
            }

            root.stmtNodes[i]->replacements.push_back(replacement);
        }
    }
}

void gen_and_save(string path, Env& env, RootNode& root) {
    ostringstream oss;
    oss << HEADER << endl << endl;
    oss << RETURN_TYPE << " " << env.name << gen_parameters(env) << "{" << endl;
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
        oss << desc << " (&" << ((env.tensors[i].is_out||env.tensors[i].require_grad)?"d":"") << env.tensors[i].name << ")";
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

    for (int i = 0; i < loop + 1; i++) {
        indent += ONE_TAB;
    }
    Variable loopVar = stmt.variables[loop];
    for (int i = 0; i < stmt.replacements.size(); i++) {
        if (stmt.replacements[i].indexToReplace == loop) {
            loopVar = stmt.replacements[i].subtitute;
        }
    }

    string var = loopVar.name;
    int lb = loopVar.lowerBound;
    int ub = loopVar.upperBound;

    // for (int i = 0; i < 32; ++i)
    oss << indent << "for (int " << var << " = " << lb << "; " << var << " < " << ub << "; ++" << var << ") {" << endl;

    if (loop < stmt.variables.size() - 1) {
        oss << gen_loop(env, stmt, loop + 1);
    } else {
        oss << gen_replace_if(env, stmt, loop + 1);
    }
    oss << indent << "}" << endl;
    return oss.str();
}

string gen_replace_expr(StmtNode& stmt, ReplacementNode& replacement) {
    string expr = replacement.subtitute.name;
    if (replacement.opWith == Operation::plus) {
        // 这里生成替换变量表达式，符号需要反过来
        expr.append(" - ");
    } else if (replacement.opWith == Operation::minus) {
        expr.append(" + ");
    }

    if (replacement.withConst) {
        expr.append(to_string(replacement.withConstVal));
    } else {
        expr.append(stmt.variables[replacement.withVariableIndex].name);
    }
    return expr;
}

string gen_replace_if(Env& env, StmtNode& stmt, int loop) {
    // 不存在替换变量，最后一层内还需要套一个if
    if (stmt.replacements.size() == 0) {
        return gen_real_expr(env, stmt, loop);
    }

    // 存在替换变量，最后一层内还需要套一个if
    ostringstream oss;
    string indent = "";

    for (int i = 0; i < loop + 1; i++) {
        indent += ONE_TAB;
    }
    
    oss << indent << "if (";

    // like this: (h - p >= 0) && (h - p < 3) && (w - q >= 0) && (w - q < 3)
    for (int i = 0; i < stmt.replacements.size(); i++) {
        string expr = gen_replace_expr(stmt, stmt.replacements[i]);
        oss << "(" << expr << " >= " << stmt.variables[stmt.replacements[i].indexToReplace].lowerBound << ")";
        oss << " && ";
        oss << "(" << expr << " < " << stmt.variables[stmt.replacements[i].indexToReplace].upperBound << ")";
        if (i < stmt.replacements.size() - 1) {
            oss << " && ";
        }
    }

    oss << ") {" << endl;
    oss << gen_real_expr(env, stmt, loop + 1);
    oss << indent << "}" << endl;
    return oss.str();
}

string gen_real_expr(Env& env, StmtNode& stmt, int loop) {
    ostringstream oss;
    string indent = "";

    for (int i = 0; i < loop + 1; i++) {
        indent += ONE_TAB;
    } 
    oss << indent << gen_lhs(env, stmt) << " += " << gen_rhs(env, stmt, *(stmt.rhsNode)) << ";" << endl;
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

string gen_lhs(Env& env, StmtNode& stmt) {
    ostringstream oss;
    oss <<"d";
    oss << env.tensors[stmt.lhsNode->tRefNode->paramterIndex].name;
    vector<IdExprNode*> & lhsIdExprList = stmt.lhsNode->tRefNode->aListNode->idExprList;
    for (int i = 0; i < lhsIdExprList.size(); i++) {
        if(lhsIdExprList[i]->op.size() == 0) {
            // 无替换变量
            oss << "[" << lhsIdExprList[i]->ids[0] << "]";
        } else {
            string suspectName = lhsIdExprList[i]->ids[lhsIdExprList[i]->ids.size() - 1];
            for (int j = 0; j < stmt.replacements.size(); j++) {
                if (suspectName.compare(stmt.variables[stmt.replacements[j].indexToReplace].name) == 0) {
                    oss << "[" << stmt.replacements[j].subtitute.name << "]";
                    break;
                }
            }
        }
    }
    return oss.str();
}

string gen_rhs(Env& env, StmtNode& stmt, RHSNode& rhsNode) {
    switch (rhsNode.type) {
    case RHSType::binary:
        return gen_rhs(env, stmt, *(rhsNode.lnode)) + " " + get_op_string(rhsNode.op) + " " + gen_rhs(env, stmt, *(rhsNode.rnode));
    case RHSType::uniary:
        return "(" + gen_rhs(env, stmt, *(rhsNode.lnode)) + ")";
    case RHSType::tref:
        return gen_tref(env, stmt, *(rhsNode.tRefNode));
    case RHSType::sref:
        return gen_sref(env, *(rhsNode.sRefNode));
    case RHSType::constref:
        return rhsNode.constNode->isInt ? to_string(rhsNode.constNode->intVal) : to_string(rhsNode.constNode->floatVal);
    default:
        cout << "ERROR" << endl;
        break;
    }
}

string gen_tref(Env& env, StmtNode& stmt, TRefNode& tRefNode) {
    ostringstream oss;
    vector<IdExprNode*> & idExprList = tRefNode.aListNode->idExprList;
    // if output == true, needs "d".
    if (env.tensors[tRefNode.paramterIndex].is_out)
        oss << "d";

    oss << env.tensors[tRefNode.paramterIndex].name;
    for (int i = 0; i < idExprList.size(); i++) {
        oss << "[";
        for (int j = 0; j < idExprList[i]->ids.size(); j++) {
            bool suspectFound = false;
            string suspectName = idExprList[i]->ids[j];
            for (int k = 0; k < stmt.replacements.size(); k++) {
                if (suspectName.compare(stmt.variables[stmt.replacements[k].indexToReplace].name) == 0) {
                    suspectFound = true;
                    oss << gen_replace_expr(stmt, stmt.replacements[k]);
                    break;
                }
            }
            
            if (!suspectFound) {
                // 无替换变量
                oss << suspectName;
            }
            if (idExprList[i]->op.size() > j) {
                if (idExprList[i]->op[j] == Operation::plus) {
                    oss << "+";
                } else if (idExprList[i]->op[j] == Operation::minus) {
                    oss << "-";
                }
            }
        }
        if (idExprList[i]->num.size() == 1) {
            oss << idExprList[i]->num[0];
        }
        oss << "]";
    }
    return oss.str();
}

string gen_sref(Env& env, SRefNode& sRefNode) {
    ostringstream oss;
    oss << env.tensors[sRefNode.paramterIndex].name;
    return oss.str();
}
