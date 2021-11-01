/*
FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

1) Napisati program koji prvo procita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i ucitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
relativan_br_bodova = br_bodova/max_br_bodova*100
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LENGTH 125

typedef struct _student{
    char name[50];
    char surname[50];
    double score;
} Student;

int countRows(char* fileName);
Student* storeStudentsData(char* fileName, int rowsNum);
double storeMaxScore(Student* students, int rowsNum);
int compareDoubleNum(double a, double b);
void printStudentsData(Student* students, int rowsNum, double maxScore);

int main(){

    int rowsNum = countRows("./students.txt");

    if(rowsNum <= 0){
        printf("Empty file\n");
        return 0;
    }

    Student* students = storeStudentsData("./students.txt", rowsNum);
    double maxScore = storeMaxScore(students, rowsNum);
    // to fix -> false value of maxScore?
    printf("MAXI:  %lf\n", maxScore);
    //
    printStudentsData(students, rowsNum, 5);
    free(students);


    return 0;
    }



int countRows(char* fileName){

    int counter = 0;
    FILE* p = fopen(fileName, "r");

    if(p == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }

    char array[MAX_LENGTH];

    while(!feof(p))
    {
        fgets(array, MAX_LENGTH, p);
        counter++;
    }

    fclose(p);

    return counter;
}



Student* storeStudentsData(char* fileName, int rowsNum){

    FILE* p = fopen(fileName, "r");

    if(p == NULL)
    {
        printf("Unable to open file.");
        exit(-1);
    }

    Student* students = (Student*)malloc(sizeof(Student) * rowsNum);

    for(int i=0; i<rowsNum; i++)
        fscanf(p,"%s %s %lf", students[i].name, students[i].surname, &students[i].score);

    fclose(p);

    return students;
}



double storeMaxScore(Student* students, int rowsNum){

    double max = 0;

    for(int i=0; i<rowsNum; i++)
        if(!compareDoubleNum(students[i].score, max))
            if(students[i].score > max)
                max = students[i].score;

    return max;
}



int compareDoubleNum(double a, double b){

    if (abs(a - b) < 1e-9)
        return 1;

    else
        return 0;
}



void printStudentsData(Student* students, int rowsNum, double maxScore){

    printf("NAME\t SURNAME\t ABSOLUTE SCORE\t RELATIVE SCORE\n");

    double relativeScore;

    for(int i=0; i < rowsNum; i++){
        relativeScore = students[i].score/ maxScore;
        printf("%s\t %s\t\t %.2lf\t\t %.2lf\n", students[i].name, students[i].surname, students[i].score, relativeScore);
    }
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
*/
