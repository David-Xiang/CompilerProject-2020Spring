%{
#include "hw2c.tab.h"
#include "adt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

%}

delim      	[ \t\n]
whitespace 	{delim}+

identifier	[a-zA-Z_]([a-zA-Z_0-9])*
float		("+"|"-")?[0-9]+("."[0-9]*)?
digit      	[0-9]
integer    	{digit}+

%%

{whitespace}	{}

{identifier} 	{char * copy = new char[strlen(yytext) + 1]; strcpy(copy, yytext); yylval.string_value = copy; return ID;}
{integer}		{yylval.int_value = atoi(yytext); return INT;}
{float}			{yylval.float_value = atof(yytext); return FLOAT;}

";"			{return SEMI;}
[\<\>\=\+\-\*\/\%\(\)\[\]\|\,] {return *yytext;}

%%

int yywrap()
{
	return 1;
}
