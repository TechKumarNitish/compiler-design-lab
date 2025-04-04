%{
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A structure to store its own value and left, right child indexes */
struct tree_node {
    char val[10];
    int lc;
    int rc;
};
int ind;  // Global index for nodes

/* Nodes for syntax tree */
struct tree_node syn_tree[100];

void my_print_tree(int cur_ind);
int mknode(int lc, int rc, const char *val);
void yyerror(const char *s);
int yylex();
%}

/* Declaring a digit named token */
%token digit

%%
/* Print the tree after evaluating E */
S: E { my_print_tree($1); }
;

/* $$ is the current node's index after making the node */
/* $n -> nth term's value in the expression */
E: E '+' T { $$ = mknode($1, $3, "+"); }
 | E '-' T { $$ = mknode($1, $3, "-"); }
 | T { $$ = $1; }
 ;

T: T '*' F { $$ = mknode($1, $3, "*"); }
 | T '/' F { $$ = mknode($1, $3, "/"); }
 | F { $$ = $1; }
 ;

F: P '^' F { $$ = mknode($1, $3, "^"); }
 | P { $$ = $1; }
 ;

P: '(' E ')' { $$ = $2; }
 | digit { 
     char buf[10]; 
     sprintf(buf, "%d", yylval); 
     $$ = mknode(-1, -1, buf);
 }
 ;

%%

int main() {
    ind = 0;
    printf("Enter an expression:\n");
    yyparse();
    return 0;
}

/* Error function must accept a string argument */
void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

/* Create a new tree node */
int mknode(int lc, int rc, const char *val) {
    strcpy(syn_tree[ind].val, val);
    syn_tree[ind].lc = lc;
    syn_tree[ind].rc = rc;
    ind++;
    return ind - 1;
}

/* Print the syntax tree in DLR (preorder) traversal */
void my_print_tree(int cur_ind) {
    /* If it's a null node, return */
    if (cur_ind == -1) return;

    /* If the node is a leaf node */
    if (syn_tree[cur_ind].lc == -1 && syn_tree[cur_ind].rc == -1) {
        printf("Digit Node -> Index: %d, Value: %s\n", cur_ind, syn_tree[cur_ind].val);
    } else {
        printf("Operator Node -> Index: %d, Value: %s, Left Child Index: %d, Right Child Index: %d\n",
               cur_ind, syn_tree[cur_ind].val, syn_tree[cur_ind].lc, syn_tree[cur_ind].rc);
    }

    /* Call left and right children recursively */
    my_print_tree(syn_tree[cur_ind].lc);
    my_print_tree(syn_tree[cur_ind].rc);
}
