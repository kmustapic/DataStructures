#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxLength 1024

struct Element;
typedef struct Element* Position;
typedef struct Element
{
	int coefficient;
	int exponent;
	Position next;
} Element;

void ReadFromFile(Position, char*);
void Input(Position, int, int);
void AddPolynomials(Position, Position, Position);
void MultiplyPolynomials(Position, Position, Position);
void Print(Position);


int main(void)
{
    char fileName[50];
    char buffer[maxLength];
    FILE* f = NULL;
    struct Element head1;
    struct Element head;
    struct Element head2;
    struct Element sum;
    struct Element multiplication;
    Element p = NULL, q = NULL;

    head1.next = NULL;
    head.next = NULL;
    head2.next = NULL;
    sum.next = NULL;
    multiplication.next = NULL;

    printf("Write file name from which you want to read data: ");
    scanf("%s", fileName);
    f = fopen(fileName, "r");
    if(f == NULL)
    {
        perror("Can't open file!");
        return 0;
    }
    while(!feof(f))
    {
        fgets(buffer, maxLength, f);
        ReadFromFile(&head1, buffer);
    }

    printf("Write file name of 2nd file you wan to read data from: ");
    scanf("%s", fileName);
    f = fopen(fileName, "r");
    if(f == NULL)
    {
        perror("Can't open file!");
        return 0;
    }
    while(!feof(f))
    {
        fgets(buffer, maxLength, f);
        ReadFromFile(&head2, buffer);
    }

    p = head1.next;
    while(p != NULL)
    {
        q = (Element)malloc(sizeof(struct Element));
        q->exponent = p->exponent;
        q->coefficient = p->coefficient;
        q->next = head.next;
        head.next = q;
        p = p->next;
    }

    AddPolynomials(&sum, &head1, &head2);

    p = head1.next;
    Print(p);
    multiplyPolynomials(&multiplication, &head, &head2);
    Print(multiplication.next);


    return 0;
}



void ReadFromFile(Element head, char* buffer)
{
    int k, e, numOfBits;
    char* current = buffer;
    Element p = head, q = NULL, prev = head;
    while(strlen(current) > 1)
    {
        prev = head;
        p = prev->next;
        sscanf(current, "%d %d%n", &k, &e, &numOfBits);
        while(p != NULL)
        {
            if(e > p->exponent)
            {
                q = (Element)malloc(sizeof(struct Element));
                q->coefficient = k;
                q->exponent = e;
                q->next = prev->next;
                prev->next = q;
                current += numOfBits;
                p = head;
                break;
            }
            else if(e == p->exponent)
            {
                p->coefficient += k;
                if(p->coefficient == 0)
                {
                    prev->next = p->next;
                    free(p);
                }
                current += numOfBits;
                p = head;
                break;
            }
            prev = prev->next;
            p = p->next;
        }
        if(p == NULL)
        {
            q = (Element)malloc(sizeof(struct Element));
            q->coefficient = k;
            q->exponent = e;
            q->next = prev->next;
            prev->next = q;
            current += numOfBits;
        }

    }
}



void AddPolynomials(Element sum, Element h1, Element h2)
{
    Element q = NULL, prev = NULL;
    prev = h1;
    sum->next = prev->next;
    h2 = h2->next;
    while(h2 != NULL)
    {
        sum = prev->next;
        while(sum != NULL)
        {
            if(h2->exponent == zsum->exponent)
            {
                sum->coefficient += h2->coefficient;
                break;
            }
            if(h2->exponent > sum->exponent)
            {
                q = (Element)malloc(sizeof(struct Element));
                q->exponent = h2->exponent;
                q->coefficient = h2->coefficient;
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = prev->next;
            sum = prev->next;
        }
        if(sum == NULL)
        {
            q = (Element)malloc(sizeof(struct Element));
            q->exponent = h2->exponent;
            q->coefficient = h2->coefficient;
            q->next = prev->next;
            prev->next = q;
        }
        h2 = h2->next;
    }
}



void MultiplyPolynomials(Element multiplication, Element h1, Element h2)
{
    Element start = h2->next;
    h1 = h1->next;
    while(h1 != NULL)
    {
        h2 = start;
        while(h2 != NULL)
        {
            ReadFromFile(multiplicaton, h1->coefficient * h2->coefficient, h1->exponent + h2->exponent);
            h2 = h2->next;
        }
        h1 = h1->next;
    }
}



void Print(Element p)
{
    printf("\n\n");
    while(p != NULL)
    {
        printf("%d x^(%d)   ", p->coefficient, p->exponent);
        p = p->next;
    }
}



void Input(Element p, Element k, Element e)
{
    Element q = NULL, prev = NULL;
    prev = p;
    p = p->next;
    while(p != NULL && p->exponent > e)
    {
        prev = p;
        p = p->next;
    }
    if(p != NULL && p->exponent == e)
        p->coefficient += k;
    else
    {
        q = (Element)malloc(sizeof(struct Element));
        q->exponent = e;
        q->coefficient = k;
        q->next = p;
        prev->next = q;
    }
}
