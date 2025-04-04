%{
#include "y.tab.h"
extern int yylval;
%}

%%
[0-9]+ { yylval = atoi(yytext); return digit; }
[\t] ;  /* Ignore tabs */
[\n] return 0;  /* Stop at newline */
. return yytext[0];  /* Return character operators */
%%
