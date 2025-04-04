%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void yyerror(char *s);
int yylex(void);
%}

%token NUM INCREMENT DECREMENT PLUS MINUS MUL DIV MOD LPAREN RPAREN EOL
%left PLUS MINUS
%left MUL DIV MOD
%right POWER
%right UMINUS
%right INCREMENT DECREMENT

%%

input:
    | input line
    ;

line:
    EOL
    | expr EOL { printf("Result: %d\n", $1); printf("Enter expression (or Ctrl+C to exit): "); }
    ;

expr:
    NUM                     { $$ = $1; }
    | expr PLUS expr        { $$ = $1 + $3; }
    | expr MINUS expr       { $$ = $1 - $3; }
    | expr MUL expr         { $$ = $1 * $3; }
    | expr DIV expr         { $$ = $1 / $3; }
    | expr MOD expr         { $$ = $1 % $3; }
    | LPAREN expr RPAREN    { $$ = $2; }
    | MINUS expr %prec UMINUS { $$ = -$2; }  /* Unary minus */
    | expr POWER expr       { $$ = (int)pow($1, $3); }
    | INCREMENT expr        { $$ = $2 + 1; }   /* Prefix increment */
    | DECREMENT expr        { $$ = $2 - 1; }   /* Prefix decrement */
    | expr INCREMENT        { $$ = $1 + 1; }   /* Postfix increment */
    | expr DECREMENT        { $$ = $1 - 1; }   /* Postfix decrement */
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter expression (or Ctrl+C to exit): ");
    yyparse();
    return 0;
}
