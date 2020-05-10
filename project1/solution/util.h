#ifndef UTIL_H
#define UTIL_H

#include "adt.h"
vector<Variable> getVariableVector(vector<Variable> & v1, vector<Variable> & v2);
vector<Variable> getVariableBounds(CListNode* cListNode, AListNode* aListNode);
int setTensorsShape(Env * env, char * name, CListNode * cListNode);
#endif