%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include "adt.h"
#include "util.h"
int yylex(void);
void yyerror(char*);
RootNode * root;
#define YYPARSE_PARAM env

using namespace std;
%}

%union
{
    RootNode * rootNode;
    StmtNode * stmtNode;
    LHSNode * lhsNode;
    RHSNode * rhsNode;
    TRefNode * trefNode;
    SRefNode * srefNode;
    CListNode * clistNode;
    AListNode * alistNode;
    IdExprNode * idexprNode;
    ConstNode * constNode;
    int int_value;
    float float_value;
    char * string_value;
}

%type <rootNode> ANS P
%type <stmtNode> S
%type <lhsNode> LHS
%type <rhsNode> RHS RHS_TERM
%type <trefNode> TRef
%type <srefNode> SRef
%type <clistNode> CList
%type <alistNode> AList
%type <idexprNode> IdExpr_term IdExpr
%type <constNode> Const
%token <string_value>ID 
%token <float_value>FLOAT
%token <int_value> INT
%token SEMI
%left '<' '>'
%left '+' '-'
%left '*' '/' '%'

%%

ANS:	P 
		{
			$$ = $1;
			root = $$;
		}
	;

P:
		P S 
		{
			$$ = $1;
			$$ -> stmtNodes.push_back($2);
		}
	|	S 
		{
			$$ = new RootNode();
			$$ -> stmtNodes.push_back($1);
		}
	;

S:
		LHS '=' RHS SEMI
		{
			$$ = new StmtNode();
			$$ -> lhsNode = $1;
			$$ -> rhsNode = $3;
			$$ -> variables = getVariableVector($1 -> tRefNode -> variables, $3 -> variables);
		}
	;

LHS:	TRef
		{
			$$ = new LHSNode();
			$$ -> tRefNode = $1;
		}
	;

RHS:	RHS '+' RHS
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::binary;
			$$ -> lnode = $1;
			$$ -> rnode = $3;
			$$ -> op = Operation::plus;
			$$ -> variables = getVariableVector($1 -> variables, $3 -> variables);
		}
	|	RHS '-' RHS
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::binary;
			$$ -> lnode = $1;
			$$ -> rnode = $3;
			$$ -> op = Operation::minus;
			$$ -> variables = getVariableVector($1 -> variables, $3 -> variables);
		}
	|	RHS_TERM
		{
			$$ = $1;
		}
	;

RHS_TERM:
		RHS '*' RHS
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::binary;
			$$ -> lnode = $1;
			$$ -> rnode = $3;
			$$ -> op = Operation::times;
			$$ -> variables = getVariableVector($1 -> variables, $3 -> variables);
		}
	|	RHS '/' RHS
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::binary;
			$$ -> lnode = $1;
			$$ -> rnode = $3;
			$$ -> op = Operation::divide;
			$$ -> variables = getVariableVector($1 -> variables, $3 -> variables);
		}
	|	RHS '%' RHS
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::binary;
			$$ -> lnode = $1;
			$$ -> rnode = $3;
			$$ -> op = Operation::mod;
			$$ -> variables = getVariableVector($1 -> variables, $3 -> variables);
		}
	|	RHS '/' '/' RHS
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::binary;
			$$ -> lnode = $1;
			$$ -> rnode = $4;
			$$ -> op = Operation::floor_divide;
			$$ -> variables = getVariableVector($1 -> variables, $4 -> variables);
		}
	|	'(' RHS ')'
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::uniary;
			$$ -> lnode = $2;
			$$ -> variables = $2 -> variables;
		}
	|	TRef
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::tref;
			$$ -> tRefNode = $1;
			$$ -> variables = $1 -> variables;
		}
	| 	SRef
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::sref;
			$$ -> sRefNode = $1;
		}
	|	Const
		{
			$$ = new RHSNode();
			$$ -> type = RHSType::constref;
			$$ -> constNode = $1;
		}
	;

Const:	FLOAT
		{
			$$ = new ConstNode();
			$$ -> isInt = false;
			$$ -> floatVal = $1;
		}
	|	INT
		{
			$$ = new ConstNode();
			$$ -> isInt = true;
			$$ -> intVal = $1;
		}
	;

CList:	CList ',' Const
		{
			$$ = $1;
			$1 -> shape.push_back($3 -> intVal);
		}
	|	Const
		{
			$$ = new CListNode();
			$$ -> shape.push_back($1 -> intVal);
		}
	;

TRef:	ID '<' CList '>' '[' AList ']'
		{
			$$ = new TRefNode();
			$$ -> cListNode = $3;
			$$ -> aListNode = $6;
			$$ -> variables = getVariableBounds($3, $6);
			// cout << "length of ID: " << strlen($1) << endl;
			$$ -> paramterIndex = setTensorsShape((Env *)env, $1, $3);
		}
	;

SRef:	ID '<' CList '>'
		{
			$$ = new SRefNode();
			$$ -> cListNode = $3;
			$$ -> paramterIndex = setTensorsShape((Env *)env, $1, $3);
		}
	;


AList:	AList ',' IdExpr
		{
			$$ = $1;
			$$ -> idExprList.push_back($3);
		}
	|	IdExpr
		{
			$$ = new AListNode();
			$$ -> idExprList.push_back($1); 
		}
	;

IdExpr:	IdExpr_term '+' IdExpr_term
		{
			$$ = new IdExprNode();
			$$ -> expr = $1 -> expr + '+' + $3 -> expr;
			$$ -> ids.insert($$ -> ids.end(), $1 -> ids.begin(), $1 -> ids.end());
			$$ -> ids.insert($$ -> ids.end(), $3 -> ids.begin(), $3 -> ids.end());
		}
	|	IdExpr_term '+' INT
		{
			$$ = new IdExprNode();
			$$ -> expr = $1 -> expr + '+' + to_string($3);
			$$ -> ids = $1 -> ids;
		}
	|	IdExpr_term '-' INT
		{
			$$ = new IdExprNode();
			$$ -> expr = $1 -> expr + '-' + to_string($3);
			$$ -> ids = $1 -> ids;
		}
	| 	IdExpr_term
		{
			$$ = $1;
		}
	;

IdExpr_term:	ID
		{
			$$ = new IdExprNode();
			$$ -> expr = $1;
			$$ -> ids.push_back($1);
		}
	|	IdExpr '*' INT
		{
			$$ = new IdExprNode();
			$$ -> expr = $1 -> expr + '*' + to_string($3);
			$$ -> ids = $1 -> ids;
		}
	|	IdExpr '/' '/' INT
		{
			$$ = new IdExprNode();
			$$ -> expr = $1 -> expr + '/' + to_string($4);
			$$ -> ids = $1 -> ids;
		}
	|	'(' IdExpr ')'
		{
			$$ = new IdExprNode();
			$$ -> expr = '(' + $2 -> expr + ')';
			$$ -> ids = $2 -> ids;
			delete $2;
		}
	;

%%

void yyerror(char *msg){
	fprintf(stderr,"Error:  %s\n",msg);
}