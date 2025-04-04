%{
#include<stdio.h>
#include<string.h>
#include<math.h>
void validateFourDigit(char*);
int isAscending(const char *);
int isDigitSumMod9(char* );
void validateCongruentMod5(char*);
void isContainAtLeastTwo5(char*);
%}

%option noyywrap

%%
[0-9]*00|[0-9]*222[0-9]* {printf("ACCEPTED\n");}
1[01]* {validateCongruentMod5(yytext);}
[0-9]*1[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9] {printf("ACCEPTED\n");}
[0-9][0-9][0-9][0-9]     {validateFourDigit(yytext);}
@        {return 1;}
.+       {isContainAtLeastTwo5(yytext);}
\n          {}
%%

void isContainAtLeastTwo5(char* text){
    int n=strlen(text);
    if(n<5){
        printf("NOT ACCEPTED\n");
        return;
    }
    int count=0;
    int i=0;
    while(i<5){
        if(text[i]=='5') count++;
        i++;
    }
    if(count<2){
        printf("NOT ACCEPTED\n");
        return;
    }
    int j=0;
    while(i<n){
        if(text[j]=='5') count--;
        if(text[i]=='5') count++;
        if(count<2){
            printf("NOT ACCEPTED\n");
            return;
        }
        j++;
        i++;
    }
    printf("ACCEPTED\n");
}

void validateCongruentMod5(char* binary){
    int length = strlen(binary);
    int result = 0;

    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            result += pow(2, length - 1 - i);
        } 
    }
    if(result%5==0) printf("ACCEPTED\n");
    else printf("NOT ACCEPTED\n");
}

int isAscending(const char *number) {
   
    for (int i = 0; i < 4; i++) {
        if (number[i] >= number[i + 1]) {
            return 0; 
        }
    }
    return 1; 
}

int isDigitSumMod9(char* text){
    int i=0;
    int num=0;
    while(i<3){
        int digit=text[i]-'0';
        int num=num*10+digit;
        i++;
    }
    if(num%9==0) return 1;
    return 0;

}

void validateFourDigit(char* text){
    if(isAscending(text) || isDigitSumMod9(text)){
        printf("ACCEPTED\n");
    }else{
        printf("NOT ACCEPTED\n");
    }
}

int main(){
    yylex();

    return 0;
}