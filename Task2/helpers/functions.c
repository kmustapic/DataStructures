#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Position CreatePerson(char* name, char* surname, int birthyear)
{
    Position newPos = NULL;
    newPos = (Position)malloc(sizeof(Person));

    if(!newPos)
    {
        perror("Can't allocate!\n");
        return EXIT_FAILURE;
    }

    strcpy(newPos->name, name);
    strcpy(newPos->surname, surname);
    newPos->birthYear = birthyear;
    newPos->next = NULL;

    return newPos;
}



int InsertAfterChosen(Position pos, Position newPos)
{
    newPos->next = pos->next;
    pos->next = newPos;

    return EXIT_SUCCESS;
}



int StartAtStart(Position head, char* name, char* surname, int birthYear)
{
    Position newPos = NULL;
    newPos = (Position)malloc(sizeof(Person));
    if(!newPos)
    {
        perror("Can't allocate!\n");
        return EXIT_FAILURE;
    }
    newPos = CreatePerson(name, surname, birthYear);
    if(!newPos)
    {
        return EXIT_FAILURE;
    }
    InsertAfterChosen(head, newPos);

    return EXIT_SUCCESS;
}



int InsertAfterCurrentLast(Position head, char* name, char* surname, int birthYear)
{
  Position newPos = NULL;
  Position last = NULL;

  newPos = CreatePerson(name, surname, birthYear);
  if(!newPos)
  {
      return EXIT_FAILURE;
  }
  InsertAfterChosen(last, newPos);

  return EXIT_SUCCESS;
}



Position FindLast(Position head)
{
    Position temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    return temp;
}



int InsertAfterLast(Position Head, char* name, char* surname, int birthyear)
{
    Position newPosition = NULL;
    Position last = NULL;

    newPosition = CreatePerson(name, surname, birthyear);
    if(!newPosition)
    {
        return EXIT_FAILURE;
    }
    InsertAfterChosen(last, newPosition);

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



int Delete(Position head, Position pos)
{
	Position temp = pos;
	if(temp == NULL)
    {
        printf("Failed Argument Error\n");
        return EXIT_FAILURE;
    }
	while (head != NULL)
	{
		if (head->next == temp)
		{
			head->next = temp->next;
			free(pos);
		}
		head = head->next;
	}

	return EXIT_SUCCESS;
}



int Print(Position first)
{
    Position temp = first;
    int counter = 0;

    printf("STUDENTS LIST:\n");
	while (temp)
	{
		printf("NAME: %s, SURNAME: %s, YEARS: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
		counter++;
	}
	if(counter == 0)
        printf("List is empty\n");

	return EXIT_SUCCESS;
}
