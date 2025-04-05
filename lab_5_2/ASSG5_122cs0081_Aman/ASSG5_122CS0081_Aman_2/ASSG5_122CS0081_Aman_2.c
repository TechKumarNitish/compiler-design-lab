#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_LIMIT 100

char parsing_stack[STACK_LIMIT];
int stack_index = -1;

char user_expression[STACK_LIMIT];
int expr_pointer = 0;

// Parsing table rows: E, E', T, T', F, $
// Columns: id, +, *, (, ), $
char grammar_table[6][6][10] = {
    {"TR",  "",    "",   "TR",  "",   ""},    // E → TR
    {"",    "+TR", "",   "",    "ε",  "ε"},   // E' → +TR | ε
    {"FS",  "",    "",   "FS",  "",   ""},    // T → FS
    {"",    "ε",   "*FS","",    "ε",  "ε"},   // T' → *FS | ε
    {"id",  "",    "",   "(E)", "",   ""},    // F → (E) | id
    {"",    "",    "",   "",    "",   ""}     // $
};

void push_symbol(char c) {
    if (stack_index < STACK_LIMIT - 1) {
        parsing_stack[++stack_index] = c;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

char pop_symbol() {
    if (stack_index >= 0) {
        return parsing_stack[stack_index--];
    } else {
        printf("Stack underflow\n");
        exit(1);
    }
}

void display_stack() {
    for (int i = 0; i <= stack_index; i++) {
        printf("%c", parsing_stack[i]);
    }
}

void display_input() {
    for (int i = expr_pointer; user_expression[i] != '\0'; i++) {
        printf("%c", user_expression[i]);
    }
}

int get_row_index(char c) {
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

int get_col_index(char c) {
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

void evaluate_expression() {
    push_symbol('$');
    push_symbol('E');

    printf("Stack | Input | Action\n");
    printf("----------------------\n");

    while (parsing_stack[stack_index] != '$') {
        display_stack();
        printf(" | ");
        display_input();
        printf(" | ");

        char top_element = parsing_stack[stack_index];
        char next_input = user_expression[expr_pointer];

        if (top_element == next_input) {
            pop_symbol();
            expr_pointer++;
            printf("Match %c\n", next_input);
        } else if (get_row_index(top_element) != -1 && get_col_index(next_input) != -1) {
            char* production_rule = grammar_table[get_row_index(top_element)][get_col_index(next_input)];
            if (strlen(production_rule) == 0) {
                printf("Error: No production\n");
                exit(1);
            } else if (strcmp(production_rule, "ε") == 0) {
                pop_symbol();
                printf("Reduce %c → ε\n", top_element);
            } else {
                pop_symbol();
                for (int i = strlen(production_rule) - 1; i >= 0; i--) {
                    if (production_rule[i] == 'R') push_symbol('R'); // E'
                    else if (production_rule[i] == 'S') push_symbol('S'); // T'
                    else push_symbol(production_rule[i]);
                }
                printf("Expand %c → %s\n", top_element, production_rule);
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
    scanf("%s", user_expression);
    strcat(user_expression, "$");
    evaluate_expression();
    return 0;
}