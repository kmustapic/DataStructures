#include "functions.c"

int main()
{
    Polynomial headEl1 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Polynomial headEl2 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Polynomial sumResult = {.coefficient = 0, .exponent = 0, .next = NULL};
    Polynomial multiplicationResult = {.coefficient = 0, .exponent = 0, .next = NULL};

    if(ReadFile("polynomial.txt", &headEl1, &headEl2) == EXIT_SUCCESS)
    {
        printf("\n________________________________________________");
        PrintPolynomial("\n 1st polynomial: ", &headEl1);
        PrintPolynomial("\n 2nd polynomial: ", &headEl2);
        printf("\n________________________________________________\n");

        if(AddPolynomials(&headEl1, &headEl2, &sumResult) == EXIT_SUCCESS)
        {
            PrintPolynomial("\n> Addition result: ", &sumResult);
        }
        else
        {
            perror("Error in adding polynomials!\n");
            return EXIT_FAILURE;
        }

        if(MultiplyPolynomials(&headEl1, &headEl2, &multiplicationResult) == EXIT_SUCCESS)
        {
            PrintPolynomial("\n> Multiplication result: ", &multiplicationResult);
        }
        else
        {
            perror("Error in multiplying polynomials!\n");
            return EXIT_FAILURE;
        }


    /*
        FreeMemory(&headEl1);
        FreeMemory(&headEl2);
        FreeMemory(&sumResult);
        FreeMemory(&multiplicationResult);
        */

    }

    return EXIT_SUCCESS;
}

