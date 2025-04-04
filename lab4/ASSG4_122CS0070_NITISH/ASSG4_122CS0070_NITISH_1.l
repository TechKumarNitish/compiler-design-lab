%{
#include "y.tab.h"
#include <stdio.h>
%}

%%
[0-9]+    { yylval = atoi(yytext); return NUMBER; }
[\t ]+    { /* Ignore whitespace */ }
\n        { return 0; }  // End of input
.         { return yytext[0]; }  // Operators, including '%'
%%
