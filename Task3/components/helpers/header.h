#ifndef HEADERFILE_H
#define HEADERFILE_H

#define N 100

struct Person;
typedef struct Person* Position;
typedef struct Person
{
    char name[N];
    char surname[N];
    int year;
    Position next;
}Person;

int Start(Position head, char* name, char* surname, int year);
int AddAfterChosen(Position head, char* name, char* surname, int year, char* pos);
int AddBeforeChosen(Position head, char* name, char* surname, int year, char* pos);
Position CreatePerson(char* name, char* surname, int year);
int Print(Position head);
int WriteInDoc(Position head, FILE *fp);
int DeleteAll(Position head);
int InsertDoc(Position head, FILE *fp);
int Sort(Position head);

#endif
