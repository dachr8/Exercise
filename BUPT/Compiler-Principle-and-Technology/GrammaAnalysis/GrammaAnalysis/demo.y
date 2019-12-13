%{
#include <stdio.h>
#include <ctype.h>
#define YYSTYPE double
extern int yylex();
void yyerror(const char *s);
%}

%token NUM
 
%%

line:	E'\n'	{printf("%lf\n", $1); return 0;}
;
E:		E'+'T	{$$ = $1 + $3;}
		| E'-'T	{$$ = $1 - $3;}
		| T		{$$ = $1;}
		;
T:		T'*'F	{$$ = $1 * $3;}
		| T'/'F	{$$ = $1 / $3;}
		| F		{$$ = $1;}
		;
F:		'('E')'	{$$ = $2; }
		| NUM	{$$ = $1;}
		;

%%
int main(int argc, char* argv[]) {
    return yyparse();
}

void yyerror(const char *s) {
	printf("%s\n", s);
}
