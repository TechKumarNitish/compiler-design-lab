#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

char input[MAX];
int input_ptr = 0;

// Parsing table rows: E, R(E'), T, S(T'), F, $
// Columns: id, +, *, (, ), $
char parsing_table[6][6][10] = {
    {"TR",  "",    "",   "TR",  "",   ""},    // E → TR
    {"",    "+TR", "",   "",    "ε",  "ε"},   // R(E') → +TR | ε
    {"FS",  "",    "",   "FS",  "",   ""},    // T → FS
    {"",    "ε",   "*FS","",    "ε",  "ε"},   // S(T') → *FS | ε
    {"id",  "",    "",   "(E)", "",   ""},    // F → (E) | id
    {"",    "",    "",   "",    "",   ""}     // $
};

void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow\n");
        exit(1);
    }
}

void print_stack() {
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
}

void print_input() {
    for (int i = input_ptr; input[i] != '\0'; i++) {
        printf("%c", input[i]);
    }
}

int get_row(char c) {
    switch (c) {
        case 'E': return 0;
        case 'R': return 1;  // E'
        case 'T': return 2;
        case 'S': return 3;  // T'
        case 'F': return 4;
        case '$': return 5;
        default: return -1;
    }
}

int get_col(char c) {
    switch (c) {
        case 'i': return 0; // id
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

void parse() {
    push('$');
    push('E');

    printf("Stack | Input | Action\n");
    printf("----------------------\n");

    while (stack[top] != '$') {
        print_stack();
        printf(" | ");
        print_input();
        printf(" | ");

        char X = stack[top];
        char a = input[input_ptr];

        if (X == a) {
            pop();
            input_ptr++;
            printf("Match %c\n", a);
        } else if (get_row(X) != -1 && get_col(a) != -1) {
            char* production = parsing_table[get_row(X)][get_col(a)];
            if (strlen(production) == 0) {
                printf("Error: No production\n");
                exit(1);
            } else if (strcmp(production, "ε") == 0) {
                pop();
                printf("Reduce %c → ε\n", X);
            } else {
                pop();
                for (int i = strlen(production) - 1; i >= 0; i--) {
                    if (production[i] == 'R') push('R'); // E'
                    else if (production[i] == 'S') push('S'); // T'
                    else push(production[i]);
                }
                printf("Expand %c → %s\n", X, production);
            }
        } else {
            printf("Error: Invalid input\n");
            exit(1);
        }
    }

    printf("$ | $ | Success: Input is valid.\n");
}

int main() {
    printf("Enter input: ");
    scanf("%s", input);
    strcat(input, "$");
    parse();
    return 0;
}
