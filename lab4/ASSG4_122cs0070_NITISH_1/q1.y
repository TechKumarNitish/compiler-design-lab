%{
    #include <stdio.h>
    #include <stdlib.h>
    int error_flag = 0;
    int result=0;
    extern int yyerror(char*);
    extern int yylex();
    double binary_to_decimal(char *binary);
%}

%token NAME NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS 

%%
statement: NAME '=' E
         | E   {result=$1;}
;
E: E '+' E     { $$ = $1 + $3; }
 | E '-' E     { $$ = $1 - $3; }
 | E '*' E     { $$ = $1 * $3; }
 | E '/' E     { $$ = $1 / $3; }
 | '-' E %prec UMINUS { $$ = -$2; }
 | '(' E ')'   { $$ = $2; }
 | NUMBER      { $$ = $1; }
 ;

%%

int yyerror(char *s) {
    error_flag = 1;  
    return 0;
}

int main() {
    yyparse();
    if(!error_flag){
        printf("Result=%d\nEntered arithmetic expression is Valid\n", result);
    }else{
        printf("Entered arithmetic expression is Invalid\n");
    }
    return 0;
}


