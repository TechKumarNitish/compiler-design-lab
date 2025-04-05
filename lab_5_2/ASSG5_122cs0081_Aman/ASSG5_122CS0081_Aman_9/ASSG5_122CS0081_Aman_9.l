%{
#include "y.tab.h"
%}

%%

"AND"                    { return AND; }
"OR"                     { return OR; }
"NOT"                    { return NOT; }
[a-zA-Z][a-zA-Z0-9]*     { yylval = yytext[0]; return ID; }
[ \t]                    { /* Ignore whitespace */ }
\n                       { return 0; }
"("                      { return '('; }
")"                      { return ')'; }

%%

int yywrap() {
    return 1;
}

