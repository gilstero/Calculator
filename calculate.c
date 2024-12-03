#include <stdio.h>
int calculate(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b != 0)
        {
            return a / b;
        }
        else
        {
            printf("Error: Division by zero.\n");
            return 0; // Returning 0 as a default for division error
        }
    default:
        printf("Error: Invalid operator '%c'.\n", op);
        return 0; // Returning 0 for invalid operator
    }
}