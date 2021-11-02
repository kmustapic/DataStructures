#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LENGTH 125


int countRows(char* fileName)
{

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

    counter--;
    fclose(p);

    return counter;
}



Student* storeStudentsData(char* fileName, int rowsNum)
{

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



double storeMaxScore(Student* students, int rowsNum)
{

    double max = 0;

    for(int i=0; i<rowsNum; i++)
        if(!compareDoubleNum(students[i].score, max))
            if(students[i].score > max)
                max = students[i].score;

    return max;
}



int compareDoubleNum(double a, double b)
{

    if (abs(a - b) < 1e-9)
        return 1;

    else
        return 0;
}



void printStudentsData(Student* students, int rowsNum, double maxScore)
{

    printf("NAME\t SURNAME\t ABSOLUTE SCORE\t RELATIVE SCORE\n");

    double relativeScore;

    for(int i=0; i < rowsNum; i++)
    {
        relativeScore = students[i].score/ maxScore*100;
        printf("%s\t %s\t\t %.2lf\t\t %.2lf\n", students[i].name, students[i].surname, students[i].score, relativeScore);
    }
}


