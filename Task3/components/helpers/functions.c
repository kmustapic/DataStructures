#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Print(Position head)
{
    while(head != NULL)
    {
        printf("NAME: %s, SURNAME: %s, YEARS: %d\n", head->name, head->surname, head->year);
        head = head->next;
    }

    return EXIT_SUCCESS;
}



int Start(Position head, char* name, char* surname, int year)
{
    Position newPos = NULL;
    newPos = (Position)malloc(sizeof(Person));
    if(!newPos)
    {
        perror("Memory not allocated!");
        return EXIT_FAILURE;
    }
    newPos = CreatePerson(name, surname, year);
    if(!newPos)
    {
        return EXIT_FAILURE;
    }
    newPos->next = head->next;
    head->next = newPos;

    return EXIT_SUCCESS;
}



int AddAfterChosen(Position head,  char* name, char* surname, int year, char* pos)
{
    Position newPos;
    newPos = CreatePerson(name, surname, year);
    while(head->next != NULL)
    {
        if(strcmp(head->surname, pos) == 0)
        {
            newPos->next = head->next;
            head->next = newPos;
            break;
        }
        head = head->next;
    }

    return EXIT_SUCCESS;
}



Position CreatePerson(char* name, char* surname, int year)
{
    Position newPos;
    newPos = (Position)malloc(sizeof(Person));
    strcpy(newPos->name, name);
    strcpy(newPos->surname, surname);
    newPos->year = year;
    newPos->next = NULL;

    return newPos;
}



int AddBeforeChosen(Position head, char* name, char* surname, int year, char* pos)
{
    Position newPos;
    newPos = (Position)malloc(sizeof(Person));
    newPos = CreatePerson(name, surname, year);
    while(head != NULL)
    {
        if(strcmp(head->next->surname, pos) == 0)
        {
            newPos->next = head->next;
            head->next = newPos;
            break;
        }
        head = head->next;
    }

    return EXIT_SUCCESS;
}



int WriteInDoc(Position head, FILE *fp)
{
    while(head != NULL)
    {
        fprintf(fp, "NAME: %s, SURNAME: %s, YEARS: %d\n", head->name, head->surname, head->year);
        head = head->next;
    }

    return EXIT_SUCCESS;
}



int DeleteAll(Position head)
{
    Position q;
    q = (Position)malloc(sizeof(Person));
    while(head->next != NULL)
    {
        q = head->next;
        head->next = q->next;
        free(q);
    }

    return EXIT_SUCCESS;
}



int InsertDoc(Position head, FILE *fp)
{
    char name[N];
    char surname[N];
    int year;

    while(!feof(fp))
    {
        fscanf(fp, "%s %s %d", name, surname, &year);
        Start(head, name, surname, year);
    }

    return EXIT_SUCCESS;
}

int Sort(Position head)
{
    Position a = NULL;
    Position beforea = NULL;
    Position temp = NULL;
    Position end = NULL;

    while(head->next != end)
    {
        beforea = head;
        a = head->next;
        while(a->next != end)
        {
            if(strcmp(a->surname, a->next->surname) < 0)
            {
                temp = a->next;
                beforea->next = temp;
                a->next = temp->next;
                temp->next = a;

                a = temp;
            }
            beforea = a;
            a = a->next;
        }
        end = a;
    }

    return EXIT_SUCCESS;
}
