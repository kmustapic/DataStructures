#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddElToFront(PersonP headEl, char* name, char* surname, int birthYear)
{
    PersonP newPerson = NULL;
    newPerson = (PersonP)malloc(sizeof(Person));
    if(!newPerson)
    {
        perror("Memory not allocated!\n");
        return;
    }
    newPerson = CreatePerson(name, surname, birthYear);
    if(!newPerson)
    {
        perror("Memory not allocated!\n");
        return;
    }
    newPerson->next = headEl->next;
    headEl->next = newPerson;
}

PersonP CreatePerson(char* name, char* surname, int birthYear)
{
    PersonP newPerson = NULL;
    newPerson = (PersonP)malloc(sizeof(Person));
    if(!newPerson)
    {
        perror("Memory not allocated!\n");
        return NULL;
    }
    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

void PrintPersonList(PersonP currentPerson)
{
    int counter = 0;

	while(currentPerson)
	{
	    if(counter == 0)
        {
            printf("\n> STUDENTS LIST:\n\n");
            printf("\tNAME\t\tSURNAME\t\tBIRTH YEAR\n");
        }
		printf("\t%s\t\t%s\t\t%d\n", currentPerson->name, currentPerson->surname, currentPerson->birthYear);
		currentPerson = currentPerson->next;
		counter++;
	}
	if(counter == 0)
    {
         printf("\nList is empty!\n");
    }
}

void AddElAtEnd(PersonP headEl, char* name, char* surname, int birthYear)
{
    PersonP newPerson = NULL;
    PersonP lastEl = headEl;
    newPerson = (PersonP)malloc(sizeof(Person));
    if(!newPerson)
    {
        perror("Memory not allocated!\n");
        return;
    }
    newPerson = CreatePerson(name, surname, birthYear);
    if(!newPerson)
    {
        perror("Memory not allocated!\n");
        return;
    }
    while(lastEl->next != NULL)
    {
        lastEl = lastEl->next;
    }
    newPerson->next = lastEl->next;
    lastEl->next = newPerson;
}

void DeleteEl(PersonP headEl, PersonP deleteEl)
{
    if(deleteEl == NULL)
    {
        return;
    }
    while(headEl != NULL)
    {
        if(headEl->next == deleteEl)
        {
            headEl->next = deleteEl->next;
        }
        headEl = headEl->next;
    }
}

PersonP FindSurname(PersonP currentEl, char* surname)
{
    while(currentEl != NULL)
    {
        if(strcmp(surname, currentEl->surname) == 0)
        {
            return currentEl;
        }
        currentEl = currentEl->next;
    }
    printf("Person with surname %s is not enetered yet!\n", surname);

    return NULL;
}

void ExecuteTask2()
{
    Person headEl;
    PersonP deleteEl = NULL;
    headEl.next = NULL;

    printf("\nAfter adding new list elements to BEGINNING:");
    //AddElToFront(&headEl, "Ana", "Anic", 2003);
    AddElToFront (&headEl, "Leo", "Stamen", 1999);
    AddElToFront(&headEl, "Mia", "Dimsic", 2002);
    //AddElToFront(&headEl, "Marko", "Novosel", 2000);
    PrintPersonList(headEl.next);

    printf("\n\nAfter adding new list elements at END:");
    AddElAtEnd(&headEl, "Zarko", "Leko", 2007);
    AddElAtEnd(&headEl, "Ena", "Enic", 2001);
    PrintPersonList(headEl.next);

    printf("\n\nAfter DELETING CERTAIN list elements:\n");
    deleteEl = FindSurname(&headEl, "Gauffin");
    DeleteEl(&headEl, deleteEl);
    deleteEl = FindSurname(&headEl, "Dimsic");
    DeleteEl(&headEl, deleteEl);
    PrintPersonList(headEl.next);

    printf("\n\nAfter DELETING ALL list elements:\n");
    deleteEl = FindSurname(&headEl, "Enic");
    DeleteEl(&headEl, deleteEl);
    deleteEl = FindSurname(&headEl, "Leko");
    DeleteEl(&headEl, deleteEl);
    deleteEl = FindSurname(&headEl, "Stamen");
    DeleteEl(&headEl, deleteEl);
    PrintPersonList(headEl.next);
}
