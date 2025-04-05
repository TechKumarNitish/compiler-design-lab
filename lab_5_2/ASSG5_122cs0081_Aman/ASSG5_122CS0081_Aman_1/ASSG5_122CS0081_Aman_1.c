#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 100

// Global state
const char *expr;
int idx = 0;

// Structure for parse tree nodes
typedef struct TreeNode {
    char data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *newNode(char data) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void displayTree(TreeNode *node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++) printf((i % 2 == 0 || i == depth - 1) ? "|" : " ");
    if (depth > 0) printf("-- ");
    printf("%c\n", node->data);
    
    displayTree(node->left, depth + 2);
    displayTree(node->right, depth + 2);
}

char getToken() {
    return expr[idx];
}

void moveNext() {
    idx++;
}

// Recursive Descent Parsing Functions
TreeNode *parseFactor();
TreeNode *parseTerm();
TreeNode *parseExpression();

TreeNode *parseFactor() {
    if (getToken() == '(') {
        moveNext();
        TreeNode *node = parseExpression();
        if (getToken() == ')') {
            moveNext();
        } else {
            printf("Error: Missing closing parenthesis.\n");
            exit(1);
        }
        return node;
    } else if (isalpha(getToken())) {
        TreeNode *node = newNode(getToken());
        moveNext();
        return node;
    } else {
        printf("Error: Invalid character '%c'\n", getToken());
        exit(1);
    }
}

TreeNode *parseTerm() {
    TreeNode *node = parseFactor();
    while (getToken() == '*' || getToken() == '/') {
        TreeNode *newNodePtr = newNode(getToken());
        moveNext();
        newNodePtr->left = node;
        newNodePtr->right = parseFactor();
        node = newNodePtr;
    }
    return node;
}

TreeNode *parseExpression() {
    TreeNode *node = parseTerm();
    while (getToken() == '+' || getToken() == '-') {
        TreeNode *newNodePtr = newNode(getToken());
        moveNext();
        newNodePtr->left = node;
        newNodePtr->right = parseTerm();
        node = newNodePtr;
    }
    return node;
}

int main() {
    char buffer[MAX_LEN];

    printf("Enter an arithmetic expression: ");
    fgets(buffer, MAX_LEN, stdin);
    
    expr = buffer;
    TreeNode *root = parseExpression();

    if (getToken() != '\n' && getToken() != '\0') {
        printf("Error: Unexpected character '%c'\n", getToken());
        return 1;
    }

    printf("Valid Expression\n");
    printf("Parse Tree:\n");
    displayTree(root, 0);

    return 0;
}