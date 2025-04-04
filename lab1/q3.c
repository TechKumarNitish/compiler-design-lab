#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *str;
    printf("enter the string to be checked: ");
    scanf("%s", str);

    int n = strlen(str);
    char ch;
    char curState = '0';
    for(int i=0; i<n; i++)
    {   
        ch=str[i];
        // scanf("%c", &ch);
        if (ch != '0' && ch != '1')
        {
            break;
        }
        if (curState == '0')
        { 
            if (ch == '0')
                curState = '1';
            else
                curState = '0';
        }
        else if (curState == '1')
        {
            if (ch == '0')
                curState = '1';
            else
                curState = '2';
        }
        else if (curState == '2')
        {
            if (ch == '0')
                curState = '1';
            else
                curState = '0';
        }
    }

    if(curState=='2'){
        printf("string is accepted.\n");
    }else{
        printf("string is not accepted.\n");
    }

    return 0;
}