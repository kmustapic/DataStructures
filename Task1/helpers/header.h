#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

typedef struct _student
{
    char name[50];
    char surname[50];
    double score;
} Student;

int countRows(char* fileName);
Student* storeStudentsData(char* fileName, int rowsNum);
double storeMaxScore(Student* students, int rowsNum);
int compareDoubleNum(double a, double b);
void printStudentsData(Student* students, int rowsNum, double maxScore);

#endif
