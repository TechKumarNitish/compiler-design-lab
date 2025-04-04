%{
#include <stdio.h>
typedef enum {
    NONE,
    KEYWORD ,
    OPERATOR ,
    CONSTANT ,
    PUNCTUATION,
    IDENTIFIER
} Token;

Token token=NONE;
int keywordCount=0, constantCount=0, identifierCount=0, operatorCount=0, punctuationCount=0;
char keywords[1024];
char constants[1024];
char punctuations[1024];
char identifiers[1024];
char operators[1024];
void utility(char *);
void push(char*, char *);
void print(char*);
%}

keyword      int|float|double|main|return|char
punctuation  ;
operator \+|\-|\*|\/|<|>|<=|>=|==|!=|&&|\|\||!|&|\||^|~|<<|>>|=|\+=|\-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=|\+\+|\-\-|\.|->|sizeof|#|##|_Alignof
constant \".+\"|\'.+\'|0-9]*\.[0-9]*(E\-?[0-9]+)|[0-9]+
identifier [a-zA-Z_]+[0-9a-zA-Z_]*

%%
{keyword}      {token=KEYWORD; utility(yytext);}
{constant}     {token=CONSTANT; utility(yytext);}
{identifier}   {token=IDENTIFIER; utility(yytext);}
{operator}     {token=OPERATOR; utility(yytext);}
{punctuation}  {token=PUNCTUATION; utility(yytext);}
@              {token=NONE; return 0;}
\n             {}
.              {token=NONE;}

%%

void utility(char *yytext){
    switch(token){
        case KEYWORD:
            keywordCount++;
            push(keywords, yytext);
            break;

        case CONSTANT:
            constantCount++;
            push(constants, yytext);
            break;

        case OPERATOR:
            operatorCount++;
            push(operators, yytext);
            break;

        case PUNCTUATION:
            punctuationCount++;
            push(punctuations, yytext);
            break;

        case IDENTIFIER:
            identifierCount++;
            push(identifiers, yytext);
            break;
    }
}

void push(char* container, char* text){
    int n1=strlen(container);
    int n2=strlen(text);
    int i=0;
    while(i<n2)
        container[n1++]=text[i++];
    container[n1++]=' ';

}

void print(char* str){
    int n=strlen(str), i=0;
    if(n==0) {
        printf("\n");
        return;
    }
    printf(" (");
    while(i<n-1)
        printf("%c", str[i++]);
    printf(")\n");
}

int yywrap() {
    return 1;
}

int main() {
    memset(keywords, 0, sizeof(keywords));
    memset(identifiers, 0, sizeof(identifiers));
    memset(punctuations, 0, sizeof(punctuations));
    memset(operators, 0, sizeof(operators));
    memset(constants, 0, sizeof(constants));
    
    yylex();

    printf("Keywords: %d ", keywordCount);
    print(keywords);

    printf("Operators: %d ", operatorCount);
    print(operators);

    printf("Constants: %d", constantCount);
    print(constants);

    printf("Punctuations: %d ", punctuationCount);
    print(punctuations);

    printf("Identifiers: %d ", identifierCount);
    print(identifiers);

    printf("Tokens: %d\n", keywordCount+operatorCount+punctuationCount+constantCount+identifierCount);
    
    return 0;
}
