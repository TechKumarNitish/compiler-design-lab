#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

typedef struct {
    char symbol;
    int state;
} StackItem;

StackItem stack[MAX_STACK_SIZE];
int top = -1;

void push(char symbol, int state) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top].symbol = symbol;
    stack[top].state = state;
}

void pop(int count) {
    top -= count;
    if (top < -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    int ip = 0;

    printf("Enter input string: ");
    scanf("%s", input);
    strcat(input, "$");  // End marker

    push('$', 0);  // Initial state

    printf("Parsing Steps:\n");

    while (1) {
        int state = stack[top].state;
        char current = input[ip];

        if (state == 0 && strncmp(&input[ip], "id", 2) == 0) {
            printf("Shift 'id'\n");
            push('L', 5);
            ip += 2;
        } 
        else if (state == 0 && current == '=') {
            printf("Shift '='\n");
            push('=', 3);
            ip++;
        }
        else if (state == 0 && current == '*') {
            printf("Shift '*'\n");
            push('*', 4);
            ip++;
        }
        else if (state == 3 && strncmp(&input[ip], "id", 2) == 0) {
            printf("Shift 'id'\n");
            push('L', 5);
            ip += 2;
        }
        else if (state == 3 && current == '*') {
            printf("Shift '*'\n");
            push('*', 4);
            ip++;
        }
        else if (state == 3 && current == '$') {
            printf("Reduce R → L\n");
            pop(1);
            push('R', 2);
        }
        else if (state == 4 && strncmp(&input[ip], "id", 2) == 0) {
            printf("Shift 'id'\n");
            push('L', 5);
            ip += 2;
        }
        else if (state == 5) {
            if (current == '$') {
                // Reduce R → L
                printf("Reduce R → L\n");
                pop(1);
                push('R', stack[top].state == 4 ? 6 : 2);

                // Reduce L → * R
                printf("Reduce L → * R\n");
                pop(2);
                push('L', 5);

                // Reduce S → L = R (if applicable)
                if (top >= 2 && stack[top - 1].symbol == '=') {
                    printf("Reduce S → L = R\n");
                    pop(3);
                    push('S', 1);
                    printf("Success: Input accepted.\n");
                    break;
                } else {
                    printf("Error: Invalid reduction to S\n");
                    exit(1);
                }
            } else if (current == '=') {
                printf("Shift '='\n");
                push('=', 3);
                ip++;
            } else {
                printf("Error: Unexpected '%c' in state 5\n", current);
                exit(1);
            }
        }
        else if (state == 2 && current == '$') {
            printf("Reduce S → L = R\n");
            pop(3);
            push('S', 1);
            printf("Success: Input accepted.\n");
            break;
        }
        else {
            printf("Error: Invalid action (State: %d, Input: '%c')\n", state, current);
            exit(1);
        }
    }

    return 0;
}
