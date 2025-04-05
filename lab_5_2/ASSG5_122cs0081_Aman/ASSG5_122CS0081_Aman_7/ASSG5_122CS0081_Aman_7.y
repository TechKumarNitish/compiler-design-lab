%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

E: E '+' T   { printf("Addition\n"); }
 | E '-' T   { printf("Subtraction\n"); }
 | T         { /* Nothing to do */ }
 ;

T: T '*' F   { printf("Multiplication\n"); }
 | T '/' F   { printf("Division\n"); }
 | F         { /* Nothing to do */ }
 ;

F: '(' E ')' { /* Nothing to do */ }
 | NUMBER    { printf("Number: %d\n", $1); }
 ;

%%

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

