#include "back/calc.h"
#include <stdio.h>
#include <string.h>


int main() {
    char expression[MAX_SIZE] = {0};

    printf("\nEnter expression to calculate\n---> ");
    fgets(expression, MAX_SIZE, stdin);

    double var = 0;
    int length = strlen(expression);

    // Delete '\n' from expression
    if (expression[length - 1] == '\n') {
        expression[length - 1] = '\0';
    }

    int size = 0;
    token *infix = parse_str(expression, &size);
    token *postfix = to_polish(infix, size);

    // If 'x' present in expression and expression is correct, read 'x' value
    if (size && strchr(expression, 'x')) {
        printf("\nEnter variable\n---> ");
        scanf("%lf", &var);
    }

    double res = calc(postfix, var, size);

    free(infix);
    free(postfix);

    printf("Result = %f\n", res);
    
    return 0;
}