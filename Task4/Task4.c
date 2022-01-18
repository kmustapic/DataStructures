#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "functions.c"

int main()
{
    Polynomial headEl1 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Polynomial headEl2 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Polynomial sumResult = {.coefficient = 0, .exponent = 0, .next = NULL};
    Polynomial multiplicationResult = {.coefficient = 0, .exponent = 0, .next = NULL};

//

//printf("\n%d\n", headEl1.coefficient);


//printf("\nSUCCESS TEST\n");

    if(ReadFile("polynomial.txt", &headEl1, &headEl2) == EXIT_SUCCESS)
    {
        printf("\n________________________________________________");
        PrintPolynomials("\n1st polynomial: ", headEl1.next);
        PrintPolynomials("\n2nd polynomial: ", headEl2.next);
        printf("\n________________________________________________\n");

        AddPolynomials(&headEl1, &headEl2, &sumResult);
        PrintPolynomials("\nAddition result: ", sumResult.next);

        MultiplyPolynomials(&headEl1, &headEl2, &multiplicationResult);
        PrintPolynomials("\nMultiplication: result", multiplicationResult.next);

    /*
        FreeMemory(&headEl1);
        FreeMemory(&headEl2);
        FreeMemory(&sumResult);
        FreeMemory(&multiplicationResult);
        */
    }

    return EXIT_SUCCESS;
}

