#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_LIMIT 100

struct Rule {
    char head;
    char body[10];
};

struct Rule grammar[] = {
    {'E', "E+T"},
    {'E', "T"},
    {'T', "T*F"},
    {'T', "F"},
    {'F', "(E)"},
    {'F', "id"}
};

int ruleCount = 6;

char parseStack[STACK_LIMIT];
int stackTop = -1;

void pushSymbol(char c) {
    parseStack[++stackTop] = c;
}

void popSymbol() {
    if (stackTop >= 0) stackTop--;
}

void showStack() {
    for (int i = 0; i <= stackTop; i++) {
        printf("%c", parseStack[i]);
    }
    printf("\n");
}

int isVariable(char c) {
    return (c == 'E' || c == 'T' || c == 'F');
}

int attemptReduction() {
    for (int i = 0; i < ruleCount; i++) {
        int len = strlen(grammar[i].body);
        if (stackTop + 1 >= len && strncmp(parseStack + stackTop - len + 1, grammar[i].body, len) == 0) {
            stackTop -= len - 1;
            parseStack[stackTop] = grammar[i].head;
            printf("Reduce %c -> %s\n", grammar[i].head, grammar[i].body);
            showStack();
            return 1; // Reduction successful
        }
    }
    return 0; // No reduction occurred
}

void shiftSymbol(char c) {
    pushSymbol(c);
    printf("Shift %c\n", c);
    showStack();
}

int main() {
    char inputStr[STACK_LIMIT];
    int index = 0;

    printf("Enter input string: ");
    scanf("%s", inputStr);

    printf("\nShift-Reduce Steps:\n");

    while (1) {
        if (inputStr[index] == '\0' && stackTop == 0 && parseStack[stackTop] == 'E') {
            printf("\nParsing Successful\n");
            break;
        }

        if (inputStr[index] == 'i' && inputStr[index + 1] == 'd') {
            shiftSymbol('F');
            index += 2;
        } else if (inputStr[index] == '(' || inputStr[index] == ')' || inputStr[index] == '+' || inputStr[index] == '*') {
            shiftSymbol(inputStr[index++]);
        } else if (inputStr[index] == '\0') {
            if (!attemptReduction()) break; // Attempt reductions until success or failure
        } else {
            printf("\nInvalid Expression\n");
            break;
        }

        while (attemptReduction()); // Continuously attempt reductions
    }
    return 0;
}
