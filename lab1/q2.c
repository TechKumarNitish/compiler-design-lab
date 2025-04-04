#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *str;
    scanf("%s", str);

    int n = strlen(str);
    char ch;
    char curState = '0';
    for(int i=0; i<n; i++)
    {   
        ch=str[i];
        // scanf("%c", &ch);
        if (ch != 'a' && ch != 'b')
        {
            break;
        }
        if (curState == '0')
        { 
            if (ch == 'a')
                curState = '1';
            else
                curState = '3';
        }
        else if (curState == '1')
        {
            if (ch == 'a')
                curState = '2';
            else
                curState = '4';
        }
        else if (curState == '2')
        {
            if (ch == 'a')
                curState = '1';
            else
                curState = '3';
        }
        else if (curState == '3')
        {
            if (ch == 'a')
                curState = '4';
            else
                curState = '3';
        }
    }

    if(curState=='3'){
        printf("ACCEPTED\n");
    }else{
        printf("NOT ACCEPTED\n");
    }

    return 0;
}