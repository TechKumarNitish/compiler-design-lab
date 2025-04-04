#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Stack for parsing
char stack[MAX];
int top = -1;

// Error flag
int errorFlag = 0;

// Push operation for stack
void push(char symbol) {
    stack[++top] = symbol;
}

// Pop operation for stack
void pop() {
    if (top >= 0) {
        top--;
    }
}

// Perform reduce operations
int reduce() {
    if (top >= 1 && stack[top] == 'd' && stack[top - 1] == 'i') {
        pop(); pop();
        push('F');
        return 1;
    }

    if (top >= 2 && stack[top] == 'F' && stack[top - 1] == '*' && stack[top - 2] == 'T') {
        pop(); pop(); pop();
        push('T');
        return 1;
    }

    if (top >= 0 && stack[top] == 'F') {
        pop();
        push('T');
        return 1;
    }

    if (top >= 2 && stack[top] == 'T' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        pop(); pop(); pop();
        push('E');
        return 1;
    }

    return 0;
}

// Error recovery mechanism
void errorRecovery(char unexpectedToken, int position) {
    printf("Syntax Error at position %d: Unexpected token '%c'\n", position, unexpectedToken);
    printf("Error Recovery: Skipping '%c'\n", unexpectedToken);
    errorFlag = 1;
}

// Shift-Reduce parser logic with error handling
void parse(char input[]) {
    int i = 0;
    push('$'); // End of input marker

    while (input[i] != '\0') {
        if (input[i] == 'i' && input[i + 1] == 'd') {
            push('i');
            push('d');
            i += 2;
        } 
        else if (input[i] == '*' || input[i] == '/') { 
            // Error Recovery for unexpected '*' or '/'
            errorRecovery(input[i], i + 1);
            i++;
        } 
        else {
            push(input[i]);
            i++;
        }

        // Perform reduction whenever possible
        while (reduce());
    }

    // Final reductions after input is processed
    while (reduce());

    // Final condition to check for success
    if (errorFlag)
        printf("Valid Parsing Resumed\n");
    else
        printf("Success\n");
}

int main() {
    char input[MAX];

    printf("Enter the input expression: ");
    scanf("%s", input);

    strcat(input, "$");  // Append '$' as end marker

    parse(input);

    return 0;
}
