%{
 #include "y.tab.h"
 #include <stdlib.h>

 extern int yylval;
%}

%%
[0-9]+ { yylval = atoi(yytext); return DIGIT; }
[a-zA-Z] { yylval = yytext[0]; return VARIABLE; }  // Recognize variables
[\t] ;
[\n] return 0;
. return yytext[0];
%%

