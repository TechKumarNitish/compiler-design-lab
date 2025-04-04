#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX][10];
int top = -1;
char inputTokens[MAX][10];
int tokenCount = 0, ip = 0;

int tokenIndex(char *token) {
    if(strcmp(token, "id") == 0) return 0;
    if(strcmp(token, "+") == 0) return 1;
    if(strcmp(token, "*") == 0) return 2;
    if(strcmp(token, "(") == 0) return 3;
    if(strcmp(token, ")") == 0) return 4;
    if(strcmp(token, "$") == 0) return 5;
    return -1;
}

char precTable[6][6] = {
    {'>', '<', '<', ' ', '>', '>'},
    {'<', '>', '<', '<', '>', '>'},
    {'<', '>', '>', '<', '>', '>'},
    {'<', '<', '<', '<', '=', ' '},
    {' ', '>', '>', ' ', '>', '>'},
    {'<', '<', '<', '<', ' ', '='}
};

char getRelation(char *a, char *b) {
    int i = tokenIndex(a), j = tokenIndex(b);
    if(i == -1 || j == -1) return ' ';
    return precTable[i][j];
}

int isTerminal(char *token) {
    if(strcmp(token, "E") == 0 || strcmp(token, "T") == 0 || strcmp(token, "F") == 0)
        return 0;
    return 1;
}

char* getTopTerminal() {
    int i;
    for(i = top; i >= 0; i--) {
        if(isTerminal(stack[i])) return stack[i];
    }
    return NULL;
}

void push(char *str) {
    top++;
    strcpy(stack[top], str);
}

char* pop() {
    return stack[top--];
}

void shift() {
    printf("Shift %s\n", inputTokens[ip]);
    push(inputTokens[ip]);
    ip++;
}

int matchHandle(char handle[][10], int n, char *result) {
    char temp[50] = "";
    for(int i = 0; i < n; i++){
        strcat(temp, handle[i]);
        if(i < n-1) strcat(temp, " ");
    }
    if(n == 1 && strcmp(temp, "id") == 0) {
        strcpy(result, "F");
        printf("Reduce F -> id\n");
        return 1;
    }
    if(n == 3 && strcmp(handle[0], "(")==0 && strcmp(handle[1], "E")==0 && strcmp(handle[2], ")")==0) {
        strcpy(result, "F");
        printf("Reduce F -> (E)\n");
        return 1;
    }
    if(n == 3 && strcmp(handle[0], "E")==0 && strcmp(handle[1], "+")==0 && strcmp(handle[2], "T")==0) {
        strcpy(result, "E");
        printf("Reduce E -> E + T\n");
        return 1;
    }
    if(n == 3 && strcmp(handle[0], "T")==0 && strcmp(handle[1], "*")==0 && strcmp(handle[2], "F")==0) {
        strcpy(result, "T");
        printf("Reduce T -> T * F\n");
        return 1;
    }
    if(n == 1 && strcmp(temp, "F") == 0) {
        strcpy(result, "T");
        printf("Reduce T -> F\n");
        return 1;
    }
    if(n == 1 && strcmp(temp, "T") == 0) {
        strcpy(result, "E");
        printf("Reduce E -> T\n");
        return 1;
    }
    return 0;
}

void reduce() {
    char handle[MAX][10];
    int count = 0, i;
    int pos = top;
    while(pos > 0) {
        if(isTerminal(stack[pos-1])) {
            char rel = getRelation(stack[pos-1], stack[pos]);
            if(rel == '<' || rel == '=') break;
        }
        pos--;
    }
    for(i = pos; i <= top; i++) {
        strcpy(handle[count++], stack[i]);
    }
    char result[10];
    if(matchHandle(handle, count, result)) {
        top = pos - 1;
        push(result);
    } else {
        printf("Error in reduction\n");
        exit(1);
    }
}

int main() {
    char expr[200];
    fgets(expr, 200, stdin);
    if(expr[strlen(expr)-1]=='\n')
        expr[strlen(expr)-1] = '\0';
    char *token = strtok(expr, " ");
    tokenCount = 0;
    while(token != NULL) {
        strcpy(inputTokens[tokenCount++], token);
        token = strtok(NULL, " ");
    }
    strcpy(inputTokens[tokenCount], "$");
    tokenCount++;
    strcpy(stack[++top], "$");
    while(!(strcmp(stack[0], "$") == 0 && top == 1 && strcmp(stack[top], "E") == 0 && strcmp(inputTokens[ip], "$") == 0)) {
        char *a = getTopTerminal();
        char *b = inputTokens[ip];
        char rel = getRelation(a, b);
        if(rel == '<' || rel == '=' || rel == ' ')
            shift();
        else if(rel == '>')
            reduce();
        else {
            printf("Error: no relation\n");
            exit(1);
        }
    }
    if(strcmp(stack[1], "E") == 0 && strcmp(stack[0], "$") == 0 && strcmp(inputTokens[ip], "$") == 0)
        printf("Valid Expression\n");
    else
        printf("Invalid Expression\n");
    return 0;
}
