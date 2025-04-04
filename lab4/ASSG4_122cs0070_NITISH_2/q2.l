%{
    #include "y.tab.h"
    #include <string.h>
%}

%%
[01]+(\.[01]+)? {
    yylval.str = strdup(yytext);
    return BINARY;
}

. { return yytext[0]; }
\n { return 0;}
%% 
 int yywrap() { return 1; }