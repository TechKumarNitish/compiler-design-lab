#include <stdio.h>
#include<string.h>
#include <stdlib.h>
char *token;
char input[100];
int l;

int E(), T(), F();


void nextToken()
{
    // Get next token
    token++;
    l++;
}

int F()
{
   printf("F%c ", *token);
    if (*token == '(')
    {
        printf("F1%c ", *token);
        nextToken();
        int res = E();

        return res;
    }

    if ((*token) == 'a' || (*token) == 'b')
    {
        printf("F2%c ", *token);
        nextToken();
        return 1;
    }

    if (*token == ')')
    {
        printf("F3%c ", *token);
        return 1;
    }
    printf("F4%c ", *token);
    return 0;
}

int T()
{
    printf("T%c ",*token);
    int res = F();
    if (!res)
    {
        printf("T0%c ", *token);
        return 0;
    }
    if (*token == '*')
    {
        printf("T1%c ",*token);
        nextToken();
        res = T();
        return res;
    }
    if (*token == '/')
    {
        printf("T2%c ", *token);
        nextToken();
        res = T();
        return res;
    }
    printf("T3%c ",*token);
    return res;
}

int E()
{
   printf("E%c ", *token); 
    int res = T();
    if (!res)
    {
        printf("E0%c ", *token);
        return 0;
    }
    if (*token == '+')
    {
        printf("E1%c ", *token);
        nextToken();
        res = E();
        return res;
    }   
    if (*token == '-')
    {
        printf("E2%c ", *token);
        nextToken();
        res = E();
        return res;
    }
    printf("E3%c ", *token);
    return res;
}

int main()
{
    scanf("%s", input);
    token = input;
    int res = E();
    if (l==strlen(input))
        printf("Valid\n");
    else
        printf("Invalid\n");

    return 0;
}