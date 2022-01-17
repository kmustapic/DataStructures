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
         printf("\n> List is empty!\n");
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

void AddElAfterNode(PersonP headEl, char* name, char* surname, int birthYear, char* afterThisNode)
{
    PersonP newPerson = NULL;
    newPerson = (PersonP)malloc(sizeof(Person));
    newPerson = CreatePerson(name, surname, birthYear);
    while(headEl->next != NULL)
    {
        if(strcmp(headEl->surname, afterThisNode) == 0)
        {
            newPerson->next = headEl->next;
            headEl->next = newPerson;
            break;
        }
        headEl = headEl->next;
    }
}

void AddElBeforeNode(PersonP headEl, char* name, char* surname, int birthYear, char* beforeThisNode)
{
    PersonP newPerson = NULL;
    newPerson = (PersonP)malloc(sizeof(Person));
    newPerson = CreatePerson(name, surname, birthYear);
    while(headEl != NULL)
    {
        if(strcmp(headEl->next->surname, beforeThisNode) == 0)
        {
            newPerson->next = headEl->next;
            headEl->next = newPerson;
            break;
        }
        headEl = headEl->next;
    }
}

void WriteInFile(PersonP headEl, FILE *w)
{
    int counter = 0;
    headEl = headEl->next;
    while(headEl != NULL)
        {
            if(counter == 0)
            {
                fprintf(w,"NAME\t\tSURNAME\t\tBIRTH YEAR\n");
            }
            fprintf(w,"%s\t\t%s\t\t%d\n", headEl->name, headEl->surname, headEl->birthYear);
            headEl = headEl->next;
            counter++;
        }
}

void SortDescendingBySurname(PersonP headEl)
{
    PersonP prevEl = (PersonP)malloc(sizeof(Person));
    PersonP currentEl = (PersonP)malloc(sizeof(Person));
    PersonP tempEl = (PersonP)malloc(sizeof(Person));
    PersonP endEl = (PersonP)malloc(sizeof(Person));
    prevEl = NULL;
    currentEl = NULL;
    tempEl = NULL;
    endEl = NULL;

    while(headEl->next != endEl)
    {
        prevEl = headEl;
        currentEl = headEl->next;
        while(currentEl->next != endEl)
        {
            if(strcmp(currentEl->surname, currentEl->next->surname) < 0)
            {
                tempEl = currentEl->next;
                prevEl->next = tempEl;
                currentEl->next = tempEl->next;
                tempEl->next = currentEl;

                currentEl = tempEl;
            }
            prevEl = currentEl;
            currentEl = currentEl->next;
        }
    endEl = currentEl;
    }
}

void SortAscendingBySurname(PersonP headEl)
{
    PersonP prevEl = (PersonP)malloc(sizeof(Person));
    PersonP currentEl = (PersonP)malloc(sizeof(Person));
    PersonP tempEl = (PersonP)malloc(sizeof(Person));
    PersonP endEl = (PersonP)malloc(sizeof(Person));
    prevEl = NULL;
    currentEl = NULL;
    tempEl = NULL;
    endEl = NULL;

    while(headEl->next != endEl)
    {
        prevEl = headEl;
        currentEl = headEl->next;
        while(currentEl->next != endEl)
        {
            if(strcmp(currentEl->surname, currentEl->next->surname) > 0)
            {
                tempEl = currentEl->next;
                prevEl->next = tempEl;
                currentEl->next = tempEl->next;
                tempEl->next = currentEl;

                currentEl = tempEl;
            }
            prevEl = currentEl;
            currentEl = currentEl->next;
        }
    endEl = currentEl;
    }
}

void EmptyList(PersonP headEl)
{
    PersonP tempEl = (PersonP)malloc(sizeof(Person));
    tempEl = NULL;
    while(headEl->next != NULL)
    {
        tempEl = headEl->next;
        headEl->next = tempEl->next;
        free(tempEl);
    }
}

void ReadInputData(PersonP headEl, FILE *r)
{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear = 0;
    char buffer[3*MAX_SIZE];

    // For skipping a line when fscanning a .txt file
    fgets(buffer, 3*MAX_SIZE, r);
    while(!feof(r))
    {
        fscanf(r,"%s\t\t%s\t\t%d\n", name, surname, &birthYear);
        AddElToFront(headEl, name, surname, birthYear);
    }
}

void ExecuteTask3()
{
    Person headEl;
    FILE *w = NULL;
    FILE *r = NULL;

    w = fopen("students", "w");
    r = fopen("inputData.txt", "r");
    if( r == NULL)
    {
        printf("File can't be opened!\n");
        return EXIT_FAILURE;
    }
    headEl.next = NULL;

    printf("\n1) After adding new list elements to BEGINNING:");
    AddElToFront(&headEl, "Ana", "Majic", 2001);
    AddElToFront(&headEl, "Mate", "Stipic", 1999);
    PrintPersonList(headEl.next);

    printf("\n\n2) After adding new list elements at END:");
    AddElAtEnd(&headEl, "Antea", "Novak", 2002);
    AddElAtEnd(&headEl, "Sven", "Rako", 2000);
    PrintPersonList(headEl.next);

    printf("\n\n3) After adding new list element BEFORE element with surname MAJIC:");
    AddElBeforeNode(&headEl, "Tea", "Ancic", 2001, "Majic");
    PrintPersonList(headEl.next);

    printf("\n\n4) After adding new list element AFTER element with surname NOVAK:");
    AddElAfterNode(&headEl, "Tino", "Anic", 2000, "Novak");
    PrintPersonList(headEl.next);

    printf("\n\n5) After DESCENDING SORTING ALPHABETICALLY list elements by SURNAME:");
    SortDescendingBySurname(&headEl);
    PrintPersonList(headEl.next);

    printf("\n\n6) After ASCENDING SORTING ALPHABETICALLY list elements by SURNAME:");
    SortAscendingBySurname(&headEl);
    PrintPersonList(headEl.next);

    WriteInFile(&headEl, w);

    printf("\n\n7) After EMPTYING EXISTING list:");
    EmptyList(&headEl);
    PrintPersonList(headEl.next);

    printf("\n\n8) After READING NEW LIST data:");
    ReadInputData(&headEl, r);
    PrintPersonList(headEl.next);

    printf("\n\n9) After ASCENDING SORTING NEW LIST data:");
    SortAscendingBySurname(&headEl);
    PrintPersonList(headEl.next);

    fclose(r);
    fclose(w);
}
