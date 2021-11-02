/*
FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

1) Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relativan_br_bodova = br_bodova/max_br_bodova*100
*/

#include <stdlib.h>
#include "helpers/header.h"
#include "helpers/functions.c"


#define MAX_LENGTH 125

int main()
{

    int rowsNum = countRows("./students.txt");

    if(rowsNum <= 0)
    {
        printf("Empty file\n");
        return 0;
    }

    Student* students = storeStudentsData("./students.txt", rowsNum);
    double maxScore = storeMaxScore(students, rowsNum);
    printStudentsData(students, rowsNum, maxScore);
    free(students);

    return 0;
}

/*
    Tips & Tricks:

        1) EXPLANATION for "exit(-1);"
            ( https://stackoverflow.com/questions/36684728/what-does-return-1-exit-1-mean )
            ( https://www.geeksforgeeks.org/difference-between-exit-and-break-in-c-cpp/ )
            ( https://www.geeksforgeeks.org/exit0-vs-exit1-in-c-c-with-examples/ )
            ( https://www.hackerearth.com/practice/notes/return-0-vs-exit0-in-main/ )

        2) EXPLANATION for feof() function in C
            ( https://www.includehelp.com/c-programs/feof-function-in-c-language-with-example.aspx )

        3) EXPLANATION for fgets() and gets() in C language
            ( https://www.geeksforgeeks.org/fgets-gets-c-language/ )

        4) EXPLANATION for double comparison in C
            ( https://www.geeksforgeeks.org/problem-in-comparing-floating-point-numbers-and-how-to-compare-them-correctly/ )

        5) EXPLANATION when to use #include <cmath> or #include <math.h>
            ( https://www.reddit.com/r/programming/comments/7gotv/ask_reddit_do_you_use_include_cmath_or_include/ )

        6) EXPLANATION explaining problem of returning multiple values from a function in C/C++
            ( https://www.tutorialspoint.com/how-can-we-return-multiple-values-from-a-function-in-c-cplusplus )

        7) EXPLANATION return statement inside "if"
            ( https://stackoverflow.com/questions/17574391/return-inside-if-and-outside-or-in-else )

        8) EXPLANATION solving point error "1.#J" in printout
            ( https://stackoverflow.com/questions/840081/what-does-floating-point-error-1-j-mean )

        9) EXPLANATION Header files in C/C++ and its uses
            ( https://www.tutorialspoint.com/cprogramming/c_header_files.htm )

        10) EXPlANATION Why are #ifndef and #define used in C++ header files?
            ( https://www.tutorialspoint.com/cprogramming/c_header_files.htm )

        11) EXPLANATION for C Language: #endif Directive
            ( https://www.techonthenet.com/c_language/directives/endif.php )

        12) EXPLANATION How to include helper functions in C?
            ( https://stackoverflow.com/questions/34120658/how-to-include-helper-functions-in-c )
*/
