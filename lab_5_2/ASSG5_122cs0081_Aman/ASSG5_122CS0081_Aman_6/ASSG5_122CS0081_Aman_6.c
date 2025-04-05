#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Stack for parsing
char parseStack[MAX_SIZE];
int stackTop = -1;

// Error flag
int hasError = 0;

// Push operation for stack
void pushToStack(char symbol) {
    parseStack[++stackTop] = symbol;
}

// Pop operation for stack
void popFromStack() {
    if (stackTop >= 0) {
        stackTop--;
    }
}

// Perform reduce operations
int performReduction() {
    if (stackTop >= 1 && parseStack[stackTop] == 'd' && parseStack[stackTop - 1] == 'i') {
        popFromStack(); popFromStack();
        pushToStack('F');
        return 1;
    }

    if (stackTop >= 2 && parseStack[stackTop] == 'F' && parseStack[stackTop - 1] == '*' && parseStack[stackTop - 2] == 'T') {
        popFromStack(); popFromStack(); popFromStack();
        pushToStack('T');
        return 1;
    }

    if (stackTop >= 0 && parseStack[stackTop] == 'F') {
        popFromStack();
        pushToStack('T');
        return 1;
    }

    if (stackTop >= 2 && parseStack[stackTop] == 'T' && parseStack[stackTop - 1] == '+' && parseStack[stackTop - 2] == 'E') {
        popFromStack(); popFromStack(); popFromStack();
        pushToStack('E');
        return 1;
    }

    return 0;
}

// Error recovery mechanism
void handleError(char invalidToken, int pos) {
    printf("Syntax Error at position %d: Unexpected token '%c'\n", pos, invalidToken);
    printf("Error Recovery: Skipping '%c'\n", invalidToken);
    hasError = 1;
}

// Shift-Reduce parser logic with error handling
void processParsing(char expression[]) {
    int index = 0;
    pushToStack('$'); // End of input marker

    while (expression[index] != '\0') {
        if (expression[index] == 'i' && expression[index + 1] == 'd') {
            pushToStack('i');
            pushToStack('d');
            index += 2;
        } 
        else if (expression[index] == '*' || expression[index] == '/') { 
            // Error Recovery for unexpected '*' or '/'
            handleError(expression[index], index + 1);
            index++;
        } 
        else {
            pushToStack(expression[index]);
            index++;
        }

        // Perform reduction whenever possible
        while (performReduction());
    }

    // Final reductions after input is processed
    while (performReduction());

    // Final condition to check for success
    if (hasError)
        printf("Valid Parsing Resumed\n");
    else
        printf("Success\n");
}

int main() {
    char expression[MAX_SIZE];

    printf("Enter the input expression: ");
    scanf("%s", expression);

    strcat(expression, "$");  // Append '$' as end marker

    processParsing(expression);

    return 0;
}
