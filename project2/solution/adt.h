#ifndef ADT_H
#define ADT_H

#include <vector>
#include <string>
using namespace std;

class Tensor;           // ins和outs中出现的张量
class Variable;         // 在for中出现的循环变量，需要推导其取值范围
class Env;              // json文件的信息
class RootNode;
class StmtNode;
class LHSNode;          // 左值，表示一个或者多个地址（由alist规定）
class RHSNode;          // 右值，表示一个定值或者随左值alist变化的值
class TRefNode;
class SRefNode;
class ConstNode;
class CListNode;        // 表示张量形状
class AListNode;        // 表示位置参数，需要带范围
class IdExprNode;       // 在数组下标中出现的表达式，每个下标仅仅需要完整表达式string即可，无需进一步解析语法

enum Operation{
    plus,
    minus,
    times,
    divide,
    mod,
    floor_divide
};

enum RHSType{
    binary, // RHS +/-/*... RHS
    uniary, // (RHS)
    tref,
    sref,
    constref
};

class Tensor {
public:
    string name;
    vector<int> shape;
    bool is_out; // 是否为输出
    bool require_grad; // 是否需要梯度
};

class Variable {
public:
    string name;
    int lowerBound, upperBound; // lb能取到，ub取不到
    bool complex; // 是否包含多个变量
};


class Env {
public:
    string name;
    bool isInt;
    vector<Tensor> tensors; // 输入参数名称及形状，对应作业描述中的id

};

class ConstNode {
public:
    bool isInt;
    int intVal;
    float floatVal;
};

class IdExprNode {
public:
    vector<int> variableIndices; // 暂时未使用
    string expr; 
    vector<Operation> op;
    vector<int> num;
    vector<string> ids;
};

class AListNode {
public:
    vector<IdExprNode*> idExprList;
};

class CListNode {
public:
    vector<int> shape;
};

class SRefNode {
public:
    int paramterIndex;
    CListNode* cListNode;
};

class TRefNode {
public:
    int paramterIndex;
    CListNode* cListNode;
    AListNode* aListNode;
    vector<Variable> variables;     // 循环变量名称以及取值上下界
};

class RHSNode {
public:
    RHSType type;           // binary, uniary, tref, sref, constref
    RHSNode* lnode;         // binary, uniary有效，除了根RHS外，其他指针需要手动释放
    RHSNode* rnode;         // binary有效，除了根RHS外，其他指针需要手动释放
    TRefNode* tRefNode;      // tref有效
    SRefNode* sRefNode;      // sref有效
    ConstNode* constNode;    // constref有效
    Operation op;           // binary有效
    vector<Variable> variables;     // 循环变量名称以及取值上下界
    StmtNode* gradNode; // 计算梯度的表达式树的根节点。
};

class LHSNode {
public:
    TRefNode* tRefNode;
};

class StmtNode {
public:
    vector<Variable> variables;     // 循环变量名称以及取值上下界
    LHSNode* lhsNode;
    RHSNode* rhsNode;
};

class RootNode {
public:
    vector<StmtNode*> stmtNodes;
};

#endif