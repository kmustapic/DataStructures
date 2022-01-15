#ifndef HEADERFILE_H
#define HEADERFILE_H

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
void ExecuteTask2();

#endif
