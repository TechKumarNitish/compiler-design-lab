%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

char id1[100], id2[100];  // Variables to store matched IDs
%}

%token IF ELSE ID EQ LT GT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

S: IF '(' E ')' S %prec LOWER_THAN_ELSE   { printf("If statement detected\n"); }
 | IF '(' E ')' S ELSE S                  { 
        printf("If statement detected\n");
        printf("Else statement detected\n");
    }
 | statement
 ;

E: ID LT ID     { printf("Condition: %s < %s\n", id1, id2); }
 | ID GT ID     { printf("Condition: %s > %s\n", id1, id2); }
 | ID EQ ID     { printf("Condition: %s == %s\n", id1, id2); }
 ;

statement: ID '=' ID ';' { printf("Assignment: %s = %s\n", id1, id2); }
 ;

%%

int main() {
    printf("Enter a C-style if-else statement:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

