%{
 #include <ctype.h>
 #include <stdio.h>
 #include <stdlib.h>

 void yyerror(const char *s);
 int yylex();
%}

%token DIGIT VARIABLE

%%
S: E { printf("\n"); }
;

E: E '+' T { printf("+"); }
 | E '-' T { printf("-"); }
 | T
 ;

T: T '*' P { printf("*"); }
 | T '/' P { printf("/"); }
 | P
 ;

P: F '^' P { printf("^"); }
 | F
 ;

F: '(' E ')' 
 | DIGIT { printf("%d", $1); }
 | VARIABLE { printf("%c", $1); }  // Print variable
 ;

%%

// Driver Code
int main() {
    printf("Enter infix expression: ");
    yyparse(); // Parse the input
    return 0;
}

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}
