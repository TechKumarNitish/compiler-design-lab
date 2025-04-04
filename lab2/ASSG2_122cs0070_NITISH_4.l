%{
#include <stdio.h>
int keywordCount=0, constantCount=0, identifierCount=0, operatorCount=0, punctuationCount=0;
%}

keyword      int|float|double|main|return|char
punctuation  ;
operator \+|\-|\*|\/|<|>|<=|>=|==|!=|&&|\|\||!|&|\||^|~|<<|>>|=|\+=|\-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=|\+\+|\-\-|\.|->|sizeof|#|##|_Alignof
constant \".+\"|\'.+\'|0-9]*\.[0-9]*(E\-?[0-9]+)|[0-9]+
identifier [a-zA-Z_]+[0-9a-zA-Z_]*

%%
{keyword}      {keywordCount++;}
{constant}     {constantCount++;}
{identifier}   {identifierCount++;}
{operator}     {operatorCount++;}
{punctuation}  {punctuationCount++;}
@              {return 0;}
\n             {}
.              {;}

%%

int yywrap() {
    return 1;
}

int main() {
    
    yylex();

    printf("Number of Keywords: %d \n", keywordCount);

    printf("Number of Constants: %d \n", constantCount);

     printf("Number of Identifiers: %d \n", identifierCount);

    printf("Number of Operators: %d \n", operatorCount);

    printf("Number of Punctuations: %d \n", punctuationCount);

    printf("Number of Tokens are: %d\n", keywordCount+operatorCount+punctuationCount+constantCount+identifierCount);
    
    return 0;
}
