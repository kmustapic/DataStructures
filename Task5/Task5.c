/*

FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

5) Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.

*/

#define _CRT_SECURE_NO_WARNINGS
#include "components/helpers/header.h"
#include "components/helpers/functions.c"

int main()
{
    double res = 0;

    CalculatePostfixFromFile(&res, "components/postfix.txt");
    printf("RESULT: %.1lf\n", res);

    return EXIT_SUCCESS;
}
