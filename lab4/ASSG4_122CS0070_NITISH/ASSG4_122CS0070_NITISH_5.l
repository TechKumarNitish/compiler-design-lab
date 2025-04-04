/* Definitions */
d [0-9]+
a [a-zA-Z]+

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Added for strcpy
#include "y.tab.h"

extern int yylval;
extern char iden[20];
%}

%%
{d} { yylval = atoi(yytext); return digit; }
{a} { strcpy(iden, yytext); yylval = 1; return id; }
[ \t] { ; }
\n return 0;
. return yytext[0];
%%

int yywrap() {
    return 1;
}
