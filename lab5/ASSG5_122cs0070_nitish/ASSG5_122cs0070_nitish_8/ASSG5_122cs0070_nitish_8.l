%{
#include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*     { yylval = yytext[0]; return ID; }
[0-9]+                   { yylval = atoi(yytext); return NUMBER; }
[ \t]                    { /* Ignore whitespace */ }
\n                       { return 0; }
"="                      { return '='; }
"+"                      { return '+'; }
"-"                      { return '-'; }
"*"                      { return '*'; }
"/"                      { return '/'; }
"("                      { return '('; }
")"                      { return ')'; }

%%

int yywrap() {
    return 1;
}

