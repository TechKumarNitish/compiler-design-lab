#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Production {
    char lhs;
    char rhs[10];
};

struct Production productions[] = {
    {'E', "E+T"},
    {'E', "T"},
    {'T', "T*F"},
    {'T', "F"},
    {'F', "(E)"},
    {'F', "id"}
};

int numProductions = 6;

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

void pop() {
    if (top >= 0) top--;
}

void displayStack() {
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\n");
}

int isNonTerminal(char c) {
    return (c == 'E' || c == 'T' || c == 'F');
}

int tryReduce() {
    int i;
    for (i = 0; i < numProductions; i++) {
        int len = strlen(productions[i].rhs);
        if (top + 1 >= len && strncmp(stack + top - len + 1, productions[i].rhs, len) == 0) {
            top -= len - 1;
            stack[top] = productions[i].lhs;
            printf("Reduce %c -> %s\n", productions[i].lhs, productions[i].rhs);
            displayStack();
            return 1; // A reduction was made
        }
    }
    return 0; // No reduction was made
}

void shift(char c) {
    push(c);
    printf("Shift %c\n", c);
    displayStack();
}

int main() {
    char input[MAX];
    int i = 0;

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nShift-Reduce Steps:\n");

    while (1) {
        if (input[i] == '\0' && top == 0 && stack[top] == 'E') {
            printf("\nSuccess\n");
            break;
        }

        if (input[i] == 'i' && input[i + 1] == 'd') {
            shift('F');
            i += 2;
        } else if (input[i] == '(') {
            shift(input[i++]);
        } else if (input[i] == ')') {
            shift(input[i++]);
        } else if (input[i] == '+' || input[i] == '*') {
            shift(input[i++]);
        } else if (input[i] == '\0') {
            if (!tryReduce()) break; // Keep trying to reduce until success or failure
        } else {
            printf("\nInvalid Expression\n");
            break;
        }

        while (tryReduce()); // Continuously try reducing whenever possible
    }

    return 0;
}

