%{
#include "y.tab.h"
#include <string.h>

extern char id1[], id2[];  // Declare external variables
%}

%%

"if"            { return IF; }
"else"          { return ELSE; }
[a-zA-Z][a-zA-Z0-9]*  { 
                        if (id1[0] == '\0') strcpy(id1, yytext); 
                        else { strcpy(id2, yytext); }
                        return ID; 
                      }
"<"             { return LT; }
">"             { return GT; }
"=="            { return EQ; }
"="             { return '='; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
[ \t\n]+        { /* Ignore whitespace */ }
.               { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

