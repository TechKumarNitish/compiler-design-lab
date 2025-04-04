%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE* outputFile=NULL;
int isVowel(char);
void utility(char*);
%}

%option noyywrap

%%
[^ \t\n]+   {utility(yytext);}
\n          {utility(yytext);}
[ \t]       {}
%%

int isVowel(char ch){
    if(ch=='a' || ch=='e' || ch=='i'  || ch=='o' || ch=='u' || ch=='A' || ch=='E' || ch=='I'  || ch=='O' || ch=='U' )
        return 1;
    return 0;
}

void utility(char* text){
    
    if(text[0]=='\n'){
        fputs("\n", outputFile);
        return;
    }
    char buffer[1024];
    memset(buffer,0, 1024);
   
    int n=strlen(text);
    char ch=text[0];
    int i=1, k=0;
    if(!((65<=ch && ch<=90)  || (97<=ch && ch<=122) )){
        buffer[k++]=ch;
    }

    while(i<n){
        buffer[k++]=text[i++];
    }
    
    if((65<=ch && ch<=90)  || (97<=ch && ch<=122) ){
        if(!isVowel(text[0]))
            buffer[k++]=ch;
        buffer[k++]='a';
        buffer[k++]='y';
    }

    buffer[k++]=' ';
    buffer[k]='\0';

    fputs(buffer, outputFile);
}

int main(){
    char inputFilename[256];
    printf("Enter the input filename: ");
    scanf("%s", inputFilename);

    FILE *inputFile=fopen(inputFilename, "r");
    if(inputFile==NULL){
        printf("ERROR: unable to open the file %s\n", inputFilename);
        return 1;
    }
    char outputFilename[256];
    printf("Enter output filename: ");
    scanf("%s", outputFilename);

    outputFile=fopen(outputFilename, "w");
    if(outputFile!=NULL){
        yyin=inputFile;
        yylex();
    }else{
        fclose(inputFile);
        printf("ERROR: Unable to create copy file\n");
        return 1;
    }

    fclose(outputFile);
    fclose(inputFile);

    printf("content has beeen written to %s\n", outputFilename);
    

    return 0;
}