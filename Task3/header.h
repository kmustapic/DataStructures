#ifndef HEADERFILE_H
#define HEADERFILE_H
#include <stdio.h>

#define MAX_SIZE 101

struct _person;
typedef struct _person* PersonP;
typedef struct _person
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    PersonP next;
} Person;

void AddElToFront(PersonP headEl, char* name, char* surname, int birthYear);
PersonP CreatePerson(char* name, char* surname, int birthyear);
void PrintPersonList(PersonP currentPerson);
void AddElAtEnd(PersonP headEl, char* name, char* surname, int birthYear);
void DeleteEl(PersonP headEl, PersonP deletePerson);
PersonP FindSurname(PersonP currentEl, char* surname);
void AddElAfterNode(PersonP headEl, char* name, char* surname, int birthYear, char* afterThisNode);
void AddElBeforeNode(PersonP headEl, char* name, char* surname, int birthYear, char* beforeThisNode);
void WriteInTxtFile(PersonP headEl, FILE *w);
void SortDescendingBySurname(PersonP headEl);
void SortAscendingBySurname(PersonP headEl);
void EmptyList(PersonP headEl);
void ReadInputData(PersonP headEl, FILE *r);
void ExecuteTask3();

#endif
