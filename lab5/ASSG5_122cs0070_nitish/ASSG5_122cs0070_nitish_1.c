#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 100

// Global variables
const char *input;
int position = 0;

// Node structure for parse tree
typedef struct Node {
    char value;
    struct Node *left, *right;
} Node;

Node *createNode(char value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

void printParseTree(Node *node, int indent) {
    if (node == NULL) return;

    for (int i = 0; i < indent; i++) {
        if (i % 2 == 0 || i == indent - 1) printf("|");
        else printf(" ");
    }

    if (indent > 0) printf("-- ");
    printf("%c\n", node->value);

    printParseTree(node->left, indent + 2);
    printParseTree(node->right, indent + 2);
}

char currentToken() {
    return input[position];
}

void advance() {
    position++;
}

// Recursive Descent Parsing Functions
Node *F();
Node *T();
Node *E();

Node *F() {
    if (currentToken() == '(') {
        advance();
        Node *node = E();
        if (currentToken() == ')') {
            advance();
        } else {
            printf("Error: Expected ')'\n");
            exit(1);
        }
        return node;
    } else if (isalpha(currentToken())) {
        Node *node = createNode(currentToken());
        advance();
        return node;
    } else {
        printf("Error: Invalid token '%c'\n", currentToken());
        exit(1);
    }
}

Node *T() {
    Node *node = F();

    while (currentToken() == '*' || currentToken() == '/') {
        Node *newNode = createNode(currentToken());
        advance();
        newNode->left = node;
        newNode->right = F();
        node = newNode;
    }

    return node;
}

Node *E() {
    Node *node = T();

    while (currentToken() == '+' || currentToken() == '-') {
        Node *newNode = createNode(currentToken());
        advance();
        newNode->left = node;
        newNode->right = T();
        node = newNode;
    }

    return node;
}

int main() {
    char userInput[MAX_INPUT];

    printf("Enter an arithmetic expression: ");
    fgets(userInput, MAX_INPUT, stdin);

    input = userInput;

    Node *root = E();

    if (currentToken() != '\n' && currentToken() != '\0') {
        printf("Error: Unexpected token '%c'\n", currentToken());
        return 1;
    }

    printf("Valid Expression\n");
    printf("Parse Tree:\n");
    printParseTree(root, 0);

    return 0;
}

