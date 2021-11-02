#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

struct Person;
typedef struct osoba* Position;
typedef struct Person
{
    char name[N];
    char surname[N];
    int years;
    Position next;
}Person;

int start( head, char* name, char* surname, int years);
int addAfterChosen(Position head, char* name, char* surname, int years, char* pos);
int addBefore(Position head, char* name, char* surname, int years, char* pos);
Position createPerson(char* name, char* surname, int years);
int print(Position head);
int writeInDoc(Position head, FILE *f);
int deleteAll(Position head);
int insertDoc(Position head, FILE *f);
int sort(Position head);


int main(void)
{
    Person head;

    FILE *w = NULL;
    FILE *r = NULL;

    w = fopen("studenti", "w");
    r = fopen("unos.txt", "r");
    if(r == NULL || w == NULL)
        return 0;
    head.next = NULL;

    pocetak(&head, "Mijo", "Mijic", 2000);
    pocetak(&head, "Mate", "Matic", 2002);
    pocetak(&head, "Ana", "Anic", 2004);
    ispisi(head.next);

    printf("\n");
    dodajIza(&head, "Ante", "Antic", 2001, "Matic");
    ispisi(head.next);

    printf("\n");
    dodajIspred(&head, "Roko", "Rokic", 2003, "Matic");
    ispisi(head.next);

    upisiDatoteku(head.next, f);

    printf("\n");
    brisiSve(&head);
    ispisi(head.next);

    printf("\n");
    unesiDatoteku(&head, u);
    ispisi(head.next);

    printf("\n");
    sortiranje(&head);
    ispisi(head.next);

    fclose(f);
    fclose(u);
    return 0;
}

int print(Position head)
{
    while(head != NULL)
    {
        printf("NAME: %s, SURNAME: %s, YEARS: %d\n", head->name, head->surname, head->years);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int start(Position head, char* name, char* surname, int years)
{
    Position newPos = NULL;
    newPos = (Position)malloc(sizeof(Person));
    if(!newPos)
    {
        perror("Memory not allocated!");
        return -1;
    }
    newPos = createPerson(name, surname, years);
    if(!newPos)
        return -1;
    newPos->next = head->next;
    head->next = newPos;

    return EXIT_SUCCESS;
}

int addAfterChosen(Position head,  char* name, char* surname, int years, char* pos)
{
    Position newPos;
    newPos = createPerson(name, surname, years);
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

Position createPerson(char* name, char* surname, int years)
{
    Position newPos;
    newPos = (Position)malloc(sizeof(Person));
    strcpy(newPos->name, name);
    strcpy(newPos->surname, surname);
    new->years = years;
    newPos->next = NULL;

    return newPos;
}


int addBefore(Position head, char* name, char* surname, int years, char* pos)
{
    Position newPos;
    newPos = (Position)malloc(sizeof(Person));
    newPos = createPerson(name, surname, years);
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

int insertDoc(Position head, FILE *f)
{
    while(head != NULL)
    {
        fprintf(f, "NAME: %s, SURNAME: %s, YEARS: %d\n", head->name, head->surname, head->years);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int deleteAll(Position head)
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

int insertDoc(Position head, FILE *f)
{
    char name[N];
    char surname[N];
    int years;

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", name, surname, &years);
        p(head, name, surname, years);
    }
    return EXIT_SUCCESS;
}

int sort(Position head)
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

                a = t;
            }
            beforea = a;
            a = a->next;
        }
        end = a;
    }


    return EXIT_SUCCESS;
}
