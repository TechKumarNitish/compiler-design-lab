%{
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int yylex();
void yyerror(const char *s);
int result; // Stores the final computed result
int syntax_error = 0; // Flag to track invalid expressions
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%right UMINUS  // Unary minus

%start input

%%
input: E { result = $1; }
     ;

E: E '+' E    { $$ = $1 + $3; }
 | E '-' E    { $$ = $1 - $3; }
 | E '*' E    { $$ = $1 * $3; }
 | E '/' E    { 
                 if ($3 == 0) {
                     yyerror("Error: Division by zero");
                     exit(1);
                 }
                 $$ = $1 / $3; 
               }
 | E '%' E    { 
                 if ($3 == 0) {
                     yyerror("Error: Modulo by zero");
                     exit(1);
                 }
                 $$ = $1 % $3; 
               }
 | '-' E %prec UMINUS { $$ = -$2; }
 | '(' E ')'  { $$ = $2; }
 | NUMBER     { $$ = $1; }
 ;

%%
/* Error handling */
void yyerror(const char *s) {
    syntax_error = 1;  // Mark that an error occurred
}

/* Main Function */
int main() {
    if (yyparse() == 0 && syntax_error == 0) {
        printf("Result=%d\n", result);
        printf("Entered arithmetic expression is Valid\n");
    } else {
        printf("Entered arithmetic expression is Invalid\n");
    }
    return 0;
}
