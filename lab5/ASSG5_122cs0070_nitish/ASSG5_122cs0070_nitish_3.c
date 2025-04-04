#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK 100

// Parsing table for LR(0) parser
// action_table[state][terminal]
// terminals: c (0), d (1), $ (2)
int action_table[7][3] = {
    // State 0
    {3, 4, -1}, // c, d, $
    // State 1
    {-1, -1, 0}, // c, d, $ (accept)
    // State 2
    {3, 4, -1}, // c, d, $
    // State 3
    {3, 4, -1}, // c, d, $
    // State 4
    {-3, -3, -3}, // reduce C→d
    // State 5
    {-1, -1, -1}, // reduce S→CC
    // State 6
    {-2, -2, -2} // reduce C→cC
};

// goto_table[state][non-terminal]
// non-terminals: S (0), C (1)
int goto_table[7][2] = {
    // State 0
    {1, 2},
    // State 1
    {-1, -1},
    // State 2
    {-1, 5},
    // State 3
    {-1, 6},
    // State 4
    {-1, -1},
    // State 5
    {-1, -1},
    // State 6
    {-1, -1}
};

// Stack definitions
int state_stack[MAX_STACK];
int state_top = 0;

char symbol_stack[MAX_STACK];
int symbol_top = 0;

char input_buffer[100];
int input_pos = 0;

void push_state(int state, char symbol) {
    if (state_top >= MAX_STACK || symbol_top >= MAX_STACK) {
        printf("Stack overflow\n");
        exit(1);
    }
    state_stack[state_top++] = state;
    symbol_stack[symbol_top++] = symbol;
    symbol_stack[symbol_top] = '\0'; // Keep as string
}

void pop_states(int n) {
    state_top -= n;
    if (state_top < 0) {
        printf("Stack underflow\n");
        exit(1);
    }
}

void pop_symbols(int n) {
    symbol_top -= n;
    if (symbol_top < 0) {
        printf("Symbol underflow\n");
        exit(1);
    }
    symbol_stack[symbol_top] = '\0';
}

int main() {
    printf("Enter input: ");
    scanf("%s", input_buffer);
    strcat(input_buffer, "$"); // Append end marker

    // Initialize stacks
    state_stack[state_top++] = 0;
    symbol_stack[symbol_top++] = '$';
    symbol_stack[symbol_top] = '\0';

    printf("Parsing Steps:\n");
    printf("Stack | Input | Action\n");
    printf("-----------------------\n");

    while (1) {
        int current_state = state_stack[state_top - 1];
        char current_input = input_buffer[input_pos];

        int terminal_index;
        if (current_input == 'c') terminal_index = 0;
        else if (current_input == 'd') terminal_index = 1;
        else if (current_input == '$') terminal_index = 2;
        else {
            printf("Error: Invalid character '%c'\n", current_input);
            exit(1);
        }

        int action = action_table[current_state][terminal_index];

        // Print current step
        printf("%-5s | %-5s | ", symbol_stack, input_buffer + input_pos);

        if (action > 0) {
            // Shift action
            printf("Shift %c\n", current_input);
            push_state(action, current_input);
            input_pos++;
        } else if (action == 0) {
            // Accept
            printf("Success\n");
            break;
        } else if (action < 0) {
            // Reduce action
            int rule = -action;
            int pop_length;
            char lhs;
            switch (rule) {
                case 1: // S → CC
                    pop_length = 2;
                    lhs = 'S';
                    break;
                case 2: // C → cC
                    pop_length = 2;
                    lhs = 'C';
                    break;
                case 3: // C → d
                    pop_length = 1;
                    lhs = 'C';
                    break;
                default:
                    printf("Error: Invalid rule %d\n", rule);
                    exit(1);
            }

            // Check if there's enough elements to pop
            if (symbol_top < pop_length || state_top < pop_length) {
                printf("Error: Not enough elements to pop for rule %d\n", rule);
                exit(1);
            }

            // Pop states and symbols
            pop_states(pop_length);
            pop_symbols(pop_length);

            // Get new state and determine goto
            int new_state = state_stack[state_top - 1];
            int lhs_index = (lhs == 'S') ? 0 : 1;
            int goto_state = goto_table[new_state][lhs_index];

            if (goto_state == -1) {
                printf("Error: No goto for %c in state %d\n", lhs, new_state);
                exit(1);
            }

            // Push lhs and goto_state
            push_state(goto_state, lhs);

            printf("Reduce %c → ", lhs);
            switch (rule) {
                case 1: printf("CC\n"); break;
                case 2: printf("cC\n"); break;
                case 3: printf("d\n"); break;
            }
        } else {
            printf("Error: Invalid action %d\n", action);
            exit(1);
        }
    }

    return 0;
}
