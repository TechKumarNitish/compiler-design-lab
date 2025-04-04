%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
FILE* outputFile=NULL;
void utility(char*);
%}

%option noyywrap

%%
[^ \t\n]+   {utility(yytext);}
\n          {}
[ \t]       {}
%%

void utility(char* text){
    fputs(text, outputFile);
    fputs(" ", outputFile);
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