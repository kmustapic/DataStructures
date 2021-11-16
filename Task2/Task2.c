/*

FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

2) Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.

*/

#define _CRT_SECURE_NO_WARNINGS
#include "helpers/header.h"
#include "helpers/functions.c"

int main(int argc, char** argv)
{
    Person head;
    Position removing = NULL;
    head.next = NULL;

    StartAtStart(&head, "Ana", "Anic", 2003);
    //startAtStart(&head, "Mate", "Matic", 2002);
    //insertAfterLast(&head, "Mia", "Mijic", 2001);
    InsertAfterLast(&head, "Leo", "Stamenov", 2000);

	return EXIT_SUCCESS;
}
