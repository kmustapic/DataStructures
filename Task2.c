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

#include <stdio.h>
#include <stdlib.h>
#include <string.>

#define MAX_LENGTH 50

struct Person;
typedef struct Person* Position;
typedef struct Person
{
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birthYear;
    Position next;
} Person;

Position createPerson(char* name, char* surname, int birthYear);
int insertAfterChosen(Position pos, Position newPos);
int startAtStart(Position head, char* name, char* surname, int birthYear);
int insertAfterLast(Position head, char* name, char* surname, int birthYear);
Position findLast(Position head);
Position Find(Position first, char* surname)
int Delete(Position head, Position pos);
int ispis(poz prva);


int main(int argc, char** argv)
{
    Person head;
    Position removing = NULL;
    head.next = NULL;

    startAtStart(&head, "Ana", "Anic", 2003);
    //startAtStart(&head, "Mate", "Matic", 2002);
    //insertAfterLast(&head, "Mia", "Mijic", 2001);
    insertAfterLast(&head, "Leo", "Stamenov", 2000);


	return 0;
}



Position createPerson(char* name, char* surname, int birthyear)
{
    Position newPos = NULL;
    newPos = (Position)malloc(sizeof(Person));

    if(!newPos)
    {
        perror("Can't allocate!\n");
        return -1;
    }

    strcpy(newPos->name, name);
    strcpy(newPos->surname, surname);
    newPos->birthYear = birthyear;
    newPos->next = NULL;

    return newPos;
}



int insertAfterChosen(Position pos, Position newPos);
{
    newPos->next = pos->next;
    pos->next = newPos;
    return EXIT_SUCCESS;
}



int startAtStart(Position head, char* name, char* surname, int birthYear)
{
    Position newPos = NULL;
    newPos = (Position)malloc(sizeof(Person)); 
    if(!newPos)
    {
        perror("Can't allocate!\n");
        return -1;
    }
    newPos = createPerson(name, surname, birthYear);
    if(!newPosition)
        return -1;
    insertAtEnd(head, newPos);

    return EXIT_SUCCESS;
}



int insertAfterLast(Position head, char* name, char* surname, int birthYear)
{
  Position newPos = NULL;
  Position last = NULL;
  
  newPos = createPerson(name, surname, birthYear);
  if(!newPos)
    return -1;
  insertAfterChosen(last, newPos);
  
  return EXIT_SUCCESS;
}



Position findLast(Position head)
{
    Position temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp;
}



int insertAfterCurrentLast(pos Head, char* name, char* surname, int birthyear)
{
    Position newPosition = NULL;
    Position last = NULL;

    newPosition = createPerson(name, surname, birthyear);
    if(!newPosition)
        return -1;
    insertAfterChosen(last, newPosition);

    return EXIT_SUCCESS;
}



Position Find(Position first, char* surname)
{
    Position temp = first;
    while(temp != NULL)
    {
        if(strcmp(temp->surname, surname) == 0)
            return temp;
        temp = temp->next;
    }

    return NULL;
}



int delete(Position head, Position pos)
{
	Position temp = pos;
	if(temp == NULL)
    {
        printf("Failed Argument Error\n");
        return EXIT_FAILURE;
    }
	while (head != NULL)
	{
		if (head->next == t)
		{
			head->next = temp->next;
			free(pozicija);
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}



int ispis(poz prva)
{
    poz t = prva;
    int br = 0;
    printf("Vezana lista osoba:\n");
	while (t)
	{
		printf("Ime: %s, prezime: %s, godina: %d\n", t->ime, t->prezime, t->godina);
		t = t->next;
		br++;
	}
	if(br == 0)
        printf("Lista je trenutno prazna\n");
	return EXIT_SUCCESS;
}
