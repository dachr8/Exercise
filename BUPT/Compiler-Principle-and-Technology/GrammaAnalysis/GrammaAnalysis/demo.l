%{
// Declaration section
#include <stdlib.h>
#define YYSTYPE double
#include "demo.tab.h"
%}

ws		[ \t]+
digit	[0-9]
num		{digit}+(\.{digit}+)?

%%

{ws}	{}
{num}	{yylval = atof(yytext); return NUM;}
"+"		{return '+';}
"-"		{return '-';}
"*"		{return '*';}
"/"		{return '/';}
"("		{return '(';}
")"		{return ')';}
"\n"	{return '\n';}

%%

int yywrap(void) {
	return 1;  
}