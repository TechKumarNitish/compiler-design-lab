#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_symbol(char *, char);
void FIND_FIRST(char *, char);
void FIND_FOLLOW(char *, char);
void FIRST_SHOW();
void FOLLOW_SHOW();
int  CREATE_LL1_TABLE();
void PARSING_TABLE_SHOW(int);
// The LL1_PARSER function (detailed parsing sequence) is omitted as per your request

int top = 0;
int t = 0, nt = 0, cr = 0, count = 0;
char FIRST_SET[100][100], FOLLOW_SET[100][100];
char T[100], NT[100], G[100][100], STACK[100];
int LL1[100][100];

int main()
{
    int i, j, flag, num;
    char dummyStr[100];  // Not used since parsing sequence is omitted

    printf("Enter no of productions (epsilon (@)):");
    scanf("%d", &num);
    
    // Read productions and update non-terminals (NT) and terminals (T)
    for(i = 0; i < num; i++)
    {
        printf("Enter the production no %d: ", i+1);
        scanf("%s", G[cr]);
        cr++;
        int fl = 1;
        // Update non-terminals: first symbol on LHS
        for(j = 0; j < nt && fl == 1; j++)
        {
            if(NT[j] == G[cr-1][0])
                fl = 0;
        }
        if(fl == 1)
            NT[nt++] = G[cr-1][0];
        fl = 1;
        // Update terminals: examine RHS (starting at index 3, skipping "->")
        for(j = 3; G[cr-1][j] != '\0'; j++)
        {
            if(!isupper(G[cr-1][j]) && G[cr-1][j] != '@')
            {
                int k;
                for(k = 0; k < t && fl == 1; k++)
                {
                    if(T[k] == G[cr-1][j])
                        fl = 0;
                }
                if(fl == 1)
                    T[t++] = G[cr-1][j];
                fl = 1;
            }
        }
    }
    
    // Display the grammar
    printf("\nThe productions are:\n");
    for(i = 0; i < cr; i++)
        printf("%s\n", G[i]);
    printf("-------------------------------\n");

    // Compute and display FIRST and FOLLOW sets
    FIRST_SHOW();
    FOLLOW_SHOW();

    // Append '$' to terminals list
    T[t++] = '$';
    T[t] = '\0';

    // Build Predictive Parsing Table
    flag = CREATE_LL1_TABLE();
    PARSING_TABLE_SHOW(flag);

    // The detailed parsing process is omitted per your request.
    // If no conflicts occur, the grammar is LL(1).

    return 0;
}

void FIRST_SHOW()
{
    int i, j;
    char arr[100];
    for(i = 0; i < nt; i++)
    {
        arr[0] = '\0';
        FIND_FIRST(arr, NT[i]);
        for(j = 0; arr[j] != '\0'; j++)
        {
            FIRST_SET[i][j] = arr[j];
        }
        FIRST_SET[i][j] = '\0';
        count = 0;
    }
    printf("\nFIRST Sets:\n\n");
    for(i = 0; i < nt; i++)
    {
        printf("first(%c) ", NT[i]);
        for(j = 0; FIRST_SET[i][j+1] != '\0'; j++)
            printf("%c ", FIRST_SET[i][j]);
        printf("%c", FIRST_SET[i][j]);
        printf("\n");
    }
}

void FOLLOW_SHOW()
{
    int i, j;
    char arr[100];
    for(i = 0; i < nt; i++)
    {
        count = 0;
        arr[0] = '\0';
        FIND_FOLLOW(arr, NT[i]);
        for(j = 0; arr[j] != '\0'; j++)
        {
            FOLLOW_SET[i][j] = arr[j];
        }
        FOLLOW_SET[i][j] = '\0';
    }
    printf("\nFOLLOW Sets:\n\n");
    for(i = 0; i < nt; i++)
    {
        printf("follow(%c) ", NT[i]);
        for(j = 0; FOLLOW_SET[i][j+1] != '\0'; j++)
            printf("%c ", FOLLOW_SET[i][j]);
        printf("%c", FOLLOW_SET[i][j]);
        printf("\n");
    }
}

void PARSING_TABLE_SHOW(int flag)
{
    int i, j;
    if(flag == 0)
    {
        printf("\n\nPredictive Parsing Table:\n\n\t");
        // Print table header in the order: +, *, (, ), a, $
        for(j = 0; j < t; j++)
        {
            printf("\t%c", T[j]);
        }
        printf("\n----------------------------------------------------------------------------------------\n\n");
        for(i = 0; i < nt; i++)
        {
            printf("%c\t|", NT[i]);
            for(j = 0; j < t; j++)
            {
                if(LL1[i][j] != 0)
                    printf("\t%s", G[LL1[i][j]-1]);
                else
                    printf("\t_");
            }
            printf("\n\n");
        }
    }
}

void FIND_FIRST(char *arr, char ch)
{
    int i;
    if(!isupper(ch))
        add_symbol(arr, ch);
    else
    {
        for(i = 0; i < cr; i++)
        {
            if(ch == G[i][0])
            {
                if(G[i][3] == '@')
                    add_symbol(arr, '@');
                else
                    FIND_FIRST(arr, G[i][3]);
            }
        }
    }
}

void FIND_FOLLOW(char arr[], char ch)
{
    int i, j, k, l, fl = 1, flag = 1;
    if(ch == G[0][0])
        add_symbol(arr, '$');
    for(i = 0; i < cr; i++)
    {
        for(j = 3; G[i][j] != '\0' && flag == 1; j++)
        {
            if(ch == G[i][j])
            {
                flag = 0;
                if(G[i][j+1] != '\0' && isupper(G[i][j+1]))
                {
                    for(k = 0; k < nt; k++)
                    {
                        if(NT[k] == G[i][j+1])
                        {
                            for(l = 0; FIRST_SET[k][l] != '\0'; l++)
                            {
                                if(FIRST_SET[k][l] != '\0' && FIRST_SET[k][l] != '@')
                                {
                                    add_symbol(arr, FIRST_SET[k][l]);
                                }
                                if(FIRST_SET[k][l] == '@')
                                    fl = 0;
                            }
                            break;
                        }
                    }
                }
                else if(G[i][j+1] != '\0' && !isupper(G[i][j+1]))
                {
                    add_symbol(arr, G[i][j+1]);
                }
                if((G[i][j+1] == '\0' || fl == 0) && G[i][0] != ch)
                {
                    fl = 1;
                    FIND_FOLLOW(arr, G[i][0]);
                }
            }
        }
    }
}

void add_symbol(char *arr, char ch)
{
    int i, flag = 0;
    for(i = 0; arr[i] != '\0'; i++)
    {
        if(ch == arr[i])
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
    {
        arr[count++] = ch;
        arr[count] = '\0';
    }
}

int CREATE_LL1_TABLE()
{
    int i, j, k, pos, flag = 0;
    char arr[100];
    for(i = 0; i < cr; i++)
    {
        arr[0] = '\0';
        count = 0;
        FIND_FIRST(arr, G[i][3]);
        for(j = 0; j < count; j++)
        {
            if(arr[j] == '@')
            {
                FIND_FOLLOW(arr, G[i][0]);
                break;
            }
        }
        for(k = 0; k < nt; k++)
        {
            if(NT[k] == G[i][0])
            {
                pos = k;
                break;
            }
        }
        for(j = 0; j < count; j++)
        {
            if(arr[j] != '@')
            {
                int m;
                for(m = 0; m < t; m++)
                {
                    if(arr[j] == T[m])
                    {
                        if(LL1[pos][m] > 0)
                        {
                            printf("\n\nConflict occur between %s and %s rules!", G[LL1[pos][m]-1], G[i]);
                            printf("\nGiven grammar is not LL(1) grammar!\n");
                            flag = 1;
                            return flag;
                        }
                        else
                            LL1[pos][m] = i + 1;
                        break;
                    }
                }
            }
        }
    }
    return flag;
}