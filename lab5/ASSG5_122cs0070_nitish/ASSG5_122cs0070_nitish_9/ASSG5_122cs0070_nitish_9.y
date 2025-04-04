%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token ID AND OR NOT

%left OR
%left AND
%right NOT

%%

E: E OR T    { printf("OR operation\n"); }
 | T         { /* Nothing to do */ }
 ;

T: T AND F   { printf("AND operation\n"); }
 | F         { /* Nothing to do */ }
 ;

F: NOT F     { printf("NOT operation\n"); }
 | '(' E ')' { /* Nothing to do */ }
 | ID        { printf("Identifier: %c\n", $1); }
 ;

%%

int main() {
    printf("Enter a Boolean expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

