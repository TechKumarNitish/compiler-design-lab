%{
#include <stdio.h>
%}


%%
[0-9]*\.[0-9]*(E\-?[0-9]+) {printf("%s is a floating point number\n", yytext);}
EXIT {return 1;}
\n {}
%%

int yywrap(){
    return 1;
}

int main() {
   
    yylex();

   
    return 0;
}
