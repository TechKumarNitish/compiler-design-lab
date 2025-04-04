/* definition section*/
%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//#define YYSTYPE double
void yyerror(char *s);
int yylex();
float x = 0;
%}
// creating tokens whose values are given by lex 
%token ZERO ONE POINT
// following a grammer rule which is converting binary number to decimal number (float value)
%%
L: X POINT Y {printf("%f",$1+x);}
| X {printf("%d", $$);}
X: X B {$$=$1*2+$2;}
| B {$$=$1;}
Y: B Y {x=$1*0.5+x*0.5;}
| {;}
B:ZERO {$$=$1;}
|ONE {$$=$1;};
%%
// main function
int main()
{
//printf("Enter the binary number : ");
// calling yyparse function which execute grammer rules and lex
while(yyparse());
printf("\n");
}
// if any error
void yyerror(char *s)
{
fprintf(stdout,"\n%s",s);
}