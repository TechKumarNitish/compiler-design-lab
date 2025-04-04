%{
    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>

    int error_flag = 0;  

    void yyerror(const char *s);
    extern int yylex();
    extern int yylineno;

    void binary_to_decimal(char *binary);
%}

%union {
    char *str;
}

%token <str> BINARY
%type <str> start

%%
start: BINARY {
        binary_to_decimal($1);       
    }
    ;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s at line %d\n", s, yylineno);
    error_flag = 1;
}

void binary_to_decimal(char *binary) {
    if (error_flag==1)
    {
        return;
    }
    
    double decimal = 0.0;
    int i = 0, point = -1;

    // Find decimal point position
    while (binary[i] != '\0') {
        if (binary[i] == '.') {
            point = i;
            break;
        }
        i++;
    }

    // Convert integer part
    int power = (point == -1) ? i - 1 : point - 1;
    for (int j = 0; j < i; j++) {
        if (binary[j] == '.') continue;
        decimal += (binary[j] - '0') * pow(2, power--);
    }

    // Convert fractional part
    if (point != -1) {
        double frac_value = 0.0;
        double frac_weight = 0.5;
        for (int j = point + 1; binary[j] != '\0'; j++) {
            frac_value += (binary[j] - '0') * frac_weight;
            frac_weight /= 2;
        }
        decimal += frac_value;
    }
    if(decimal==(int)decimal)
        printf("%d",(int)decimal);
    else 
        printf("%lf",decimal);
}

int main() {
    while (1) {
        error_flag = 0;
        printf("\nEnter a binary number: ");
        yyparse();
    }
    return 0;
}
