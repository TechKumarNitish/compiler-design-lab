/* definitions */
%{
// including required header files
#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
// declaring a external variable yylval
extern int yylval;
%}
/* rules
if 0 is matched ,make yylval to 0 and return ZERO which is
variable in Yacc program
if 1 is matched ,make yylval to 1 and return ONE which is
variable in Yacc program
if . is matched ,return POINT which is variable in Yacc program
if line change , return 0
otherwise ,ignore*/
%%
0 {yylval=0;return ZERO;}
1 {yylval=1;return ONE;}
"." {return POINT;}
[ \t] {;}
\n return 0;
%%