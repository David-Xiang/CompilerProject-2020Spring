#include "util.h"
#include "adt.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


using namespace std;

// 合并变量取值
vector<Variable> getVariableVector(vector<Variable> & v1, vector<Variable> & v2)
{
	vector<Variable> ans;
	// 记录变量位置
	map<string, int> pos;
	for (int i = 0; i < v1.size(); ++i)
	{
		ans.push_back(Variable(v1[i]));
		pos.insert(make_pair(v1[i].name, i));
	}
	for (int i = 0; i < v2.size(); ++i)
	{
		if (pos.find(v2[i].name) != pos.end())
		{
			Variable & v = ans[pos[v2[i].name]];
			if (v.lowerBound < v2[i].lowerBound)
			{
				v.lowerBound = v2[i].lowerBound;
			}
			if (v.upperBound > v2[i].upperBound)
			{
				v.upperBound = v2[i].upperBound;
			}
		}
		else
		{
			ans.push_back(Variable(v2[i]));
		}
	}
	return ans;
}

// 找到i,j,k的上下限
vector<Variable> getVariableBounds(CListNode* cListNode, AListNode* aListNode)
{
	vector<Variable> ans;
	vector<int> & shape = cListNode -> shape;
	vector<IdExprNode*>  & nodes = aListNode -> idExprList;
	for (int i = 0; i < shape.size(); ++i)
	{
		int size = shape[i];
		IdExprNode * node = nodes[i];
		int upperBound = size;
		int lowerBound = 0;
		// int num_op = node -> op.size();
		if (node -> ids.size() == 1)
		{
			if (node -> op.size())
			{
				switch(node -> op[0])
				{
					case(Operation::plus):
					{
						upperBound -= node -> num[0];
						lowerBound = max(0, lowerBound - node -> num[0]);
						break;
					}
					case(Operation::minus):
					{
						upperBound = min(upperBound + node -> num[0], size);
						lowerBound = lowerBound + node -> num[0];
						break;
					}
					case(Operation::times):
					{
						lowerBound /= node -> num[0];
						break;
					}
					case(Operation::mod):
					{
						// TODO
						break;
					}
					case(Operation::floor_divide):
					{
						upperBound *= node -> num[0];
						break;
					}
					default:
					{
						break;
					}
				}
			}
			Variable  * var = new Variable();
			var -> name = node -> ids[0];
			var -> lowerBound = lowerBound;
			var -> upperBound = upperBound;
			var -> complex = false;
			ans.push_back(*var);
		}
		else
		{
			Variable  * var = new Variable();
			var -> name = node -> expr;
			var -> lowerBound = lowerBound;
			var -> upperBound = upperBound;
			var -> complex = true;
			ans.push_back(*var);
		}	
	}
	return ans;
}

// 向Env中填写shape，返回在Env中的index
int setTensorsShape(Env * env, char * name, CListNode * cListNode)
{
	for (int i = 0; i < env -> tensors.size(); ++i)
	{
		// cout << "Env Tensor: " << env -> tensors[i].name << endl;
		// cout << "cListNode Name: " << name << endl;
		if (name == env -> tensors[i].name)
		{
			env -> tensors[i].shape = cListNode -> shape;
			return i;
		}
	}
}