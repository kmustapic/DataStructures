/*

FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

4) Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "components/helpers/header.h"
#include "components/helpers/functions.c"

int main()
{
    Node head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
    Node head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
    Node sumResult = { .coefficient = 0, .exponent = 0, .next = NULL };
    Node multiplicationResult = { .coefficient = 0, .exponent = 0, .next = NULL };

    char fileName[MAX_LENGTH] = {0};
    EnterFileName(fileName);

    if(ReadFile(fileName, &head1, &head2) == EXIT_SUCCESS)
    {
        PrintPolynomial("1st polynomial: ", head1.next);
        PrintPolynomial("2nd polynomial: ", head2.next);

        AddPolynomials(&head1, &head2, &sumResult);
        MultiplyPolynomials(&head1, &head2, &multiplicationResult);

        PrintPolynomial("Addition: ", sumResult.next);
        PrintPolynomial("Multiplication: ", multiplicationResult.next);

        FreeMemory(&head1);
        FreeMemory(&head2);
        FreeMemory(&sumResult);
        FreeMemory(&multiplicationResult);
    }

    return EXIT_SUCCESS;
}
