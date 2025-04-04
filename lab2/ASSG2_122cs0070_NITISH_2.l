%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char *s);
%}

%%

[0-9]+          { yylval = atoi(yytext); return NUM; }
"++"            { return INCREMENT; }
"--"            { return DECREMENT; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"%"             { return MOD; }
"("             { return LPAREN; }
")"             { return RPAREN; }
\n              { return EOL; }  // Match newlines and return EOL
[ \t]           { /* Skip whitespaces */ }
.               { /* Skip other characters */ }

%%

int yywrap() {
    return 1;
}
