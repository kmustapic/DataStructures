/*

FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

3) Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.


*/

#include<stdio.h>
#include<stdlib.h>
#include "components/helpers/header.h"
#include "components/helpers/functions.c"

int main()
{
    Person head;

    FILE *w = NULL;
    FILE *r = NULL;

    w = fopen("components/students.txt", "w");
    r = fopen("components/input.txt", "r");
    if(r == NULL || w == NULL)
    {
        return EXIT_FAILURE;
    }
    head.next = NULL;

    Start(&head, "Milka", "Maric", 2002);
    Start(&head, "Matea", "Matic", 2000);
    Start(&head, "Ana", "Anic", 2004);
    Print(head.next);

    printf("\n");
    AddAfterChosen(&head, "Ante", "Antic", 2001, "Matic");
    Print(head.next);

    printf("\n");
    AddBeforeChosen(&head, "Marta", "Martic", 2003, "Matic");
    Print(head.next);

    WriteInDoc(head.next, w);

    printf("\n");
    DeleteAll(&head);
    Print(head.next);

    printf("\n");
    InsertDoc(&head, r);
    Print(head.next);

    printf("\n");
    Sort(&head);
    Print(head.next);

    fclose(w);
    fclose(r);

    return EXIT_FAILURE;
}
