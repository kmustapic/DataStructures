#ifndef HEADERFILE_H
#define HEADERFILE_H

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

Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfterChosen(Position pos, Position newPos);
int StartAtStart(Position head, char* name, char* surname, int birthYear);
int InsertAfterLast(Position head, char* name, char* surname, int birthYear);
Position FindLast(Position head);
Position Find(Position first, char* surname);
int Delete(Position head, Position pos);
int Print(Position first);

#endif
