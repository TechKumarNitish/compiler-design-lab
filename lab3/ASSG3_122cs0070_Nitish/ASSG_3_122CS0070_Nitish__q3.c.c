#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global arrays: 'stack' holds the symbols (as a string)
// and 'input' will store the input string.
char stack[100] = "";
char input[100];

// Helper function: returns nonzero if string 'str' ends with 'suffix'
int endsWith(const char *str, const char *suffix) {
    int lenStr = strlen(str);
    int lenSuffix = strlen(suffix);
    if (lenStr < lenSuffix)
        return 0;
    return strcmp(str + lenStr - lenSuffix, suffix) == 0;
}

/*
   The reduce() function checks if the current stack (which holds a sequence
   of grammar symbols) ends with any right-hand side of a production.
   If a handle is found, it “reduces” that substring by replacing it with the
   corresponding nonterminal (the left-hand side) and prints the reduction action.
   
   The production rules (with our simplified tokenization) are:
   
   (6) F -> id         represented as:  id   (we treat 'i' as id)
   (5) F -> ( E )      represented as:  (E)
   (3) T -> T * F      represented as:  T*F
   (1) E -> E + T      represented as:  E+T
   (4) T -> F          represented as:  F    (we apply this only when the stack has more than one symbol)
   (2) E -> T          represented as:  T    (again, only if the stack is not a sole symbol)
   
   Note: The order in which reductions are attempted (and conditions applied)
   is chosen so that the sample sequence of actions is roughly produced.
*/
int reduce() {
    int len;
    
    // 1. Try production (6): F -> id 
    // Check if the stack ends with "i" (representing id).
    if (endsWith(stack, "i")) {
        len = strlen(stack);
        if (stack[len - 1] == 'i') {
            // Remove the "i" and push "F" instead.
            stack[len - 1] = '\0';
            strcat(stack, "F");
            printf("Reduce F -> id\n");
            return 1;
        }
    }
    
    // 2. Try production (5): F -> (E)
    if (endsWith(stack, "(E)")) {
        len = strlen(stack);
        // Remove the last three characters "(E)" and replace with "F"
        stack[len - 3] = '\0';
        strcat(stack, "F");
        printf("Reduce F -> (E)\n");
        return 1;
    }
    
    // 3. Try production (3): T -> T * F
    if (endsWith(stack, "T*F")) {
        len = strlen(stack);
        // Remove "T*F" (three symbols) and replace with "T"
        stack[len - 3] = '\0';
        strcat(stack, "T");
        printf("Reduce T -> T * F\n");
        return 1;
    }
    
    // 4. Try production (1): E -> E + T
    if (endsWith(stack, "E+T")) {
        len = strlen(stack);
        // Remove "E+T" and replace with "E"
        stack[len - 3] = '\0';
        strcat(stack, "E");
        printf("Reduce E -> E + T\n");
        return 1;
    }
    
    // 5. Try production (4): T -> F 
    // Only perform this reduction if the stack has more than one symbol.
    if (endsWith(stack, "F") && strcmp(stack, "F") != 0) {
        len = strlen(stack);
        if (stack[len - 1] == 'F') {
            // Replace the last 'F' with 'T'
            stack[len - 1] = '\0';
            strcat(stack, "T");
            printf("Reduce T -> F\n");
            return 1;
        }
    }
    
    // 6. Try production (2): E -> T 
    // Again, only reduce if the entire stack is not just "T".
    if (endsWith(stack, "T") && strcmp(stack, "T") != 0) {
        len = strlen(stack);
        if (stack[len - 1] == 'T') {
            stack[len - 1] = '\0';
            strcat(stack, "E");
            printf("Reduce E -> T\n");
            return 1;
        }
    }
    
    // If no reduction was possible, return 0.
    return 0;
}

int main() {
    int i = 0;
    char symbol;
    
    // Print the grammar.
    printf("Simple Shift-Reduce Parser\n");
    printf("Grammar:\n");
    printf("E -> E+T | T\n");
    printf("T -> T*F | F\n");
    printf("F -> (E) | id\n\n");
    
    // Prompt the user to enter the input string.
    // (For this program, enter the expression without spaces using 'i' for id.
    //  For example, to represent: id + id * id, enter: i+i*i )
    printf("Enter the input string: ");
    scanf("%s", input);
    
    // Append an end-marker '$' to the input.
    strcat(input, "$");
    
    printf("\nParsing Actions:\n");
    
    // Continue until the end marker is reached.
    while (input[i] != '$') {
        symbol = input[i];
        i++;
        
        // Shift action: append the token to the stack.
        // For an id, we shift the token 'i' but print it as "id".
        if (symbol == 'i') {
            strcat(stack, "i");
            printf("Shift id\n");
        } else {
            // For other symbols (+, *, (, )), shift them.
            char temp[2];
            temp[0] = symbol;
            temp[1] = '\0';
            strcat(stack, temp);
            printf("Shift %s\n", temp);
        }
        
        // After every shift, repeatedly try to reduce the stack.
        while (reduce());
    }
    
    // After all input is processed, check if the stack is reduced to the start symbol.
    if (strcmp(stack, "E") == 0)
        printf("Valid Expression\n");
    else
        printf("Invalid Expression\n");
        
    return 0;
}
