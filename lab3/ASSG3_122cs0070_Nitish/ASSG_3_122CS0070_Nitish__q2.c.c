#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Global input string and index pointer.
char input[100];
int i = 0;     // Current index in input.
int error = 0; // Flag to indicate a parsing error.

// Forward declarations of recursive descent functions.
void E();
void Eprime();
void T();
void Tprime();
void F();

// Utility function: match the expected character.
void match(char expected) {
    if (input[i] == expected) {
        i++; // Consume the symbol.
    } else {
        error = 1;
        printf("Error: expected '%c' but found '%c'\n", expected, input[i]);
    }
}

// E -> T E'
void E() {
    T();
    Eprime();
}

// E' -> + T E' | epsilon
void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
    // else: epsilon production; do nothing.
}

// T -> F T'
void T() {
    F();
    Tprime();
}

// T' -> * F T' | epsilon
void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
    // else: epsilon production; do nothing.
}

// F -> (E) | ID
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        if (input[i] == ')') {
            match(')');
        } else {
            error = 1;
            printf("Error: expected ')' but found '%c'\n", input[i]);
        }
    }
    else if (isalpha(input[i])) { // Assume an ID is a single alphabet letter.
        match(input[i]);
    }
    else {
        error = 1;
        printf("Error in F(): unexpected symbol '%c'\n", input[i]);
    }
}

int main() {
    printf("Recursive descent parsing for the following grammar\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' / @\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' / @\n");
    printf("F  -> (E) / ID\n");
    printf("\nEnter the string to be checked: ");
    scanf("%s", input);

    // Start the parsing process from the start symbol E.
    E();
    
    // Check if the entire input was consumed and no error was flagged.
    if (input[i] == '\0' && error == 0)
        printf("String is accepted\n");
    else
        printf("String is not accepted\n");

    return 0;
}