/*

FESB, Split - Racunarstvo (preddiplomski studij) - 3. semestar - Strukture podataka (120) - 2021/2022

4) Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH (1024)

struct _Node;
typedef struct _Node* Position;
typedef struct _Node
{
    int coefficient;
    int exponent;
    Position next;
} Node;



int EnterFileName(char* fileName);
int ReadFile(char* fileName, Position head1, Position head2);
int ParseStringIntoList(char* buffer, Position head);
Position CreateNode(int coefficient, int exponent);
int InsertAfterNode(Position currentNode, Position newNode);
int DeleteAfterNode(Position prevNode);
int MergeNodes(Position currentNode, Position newNode);
int InsertSortedNode(Position head, Position newNode);
int CreateAndInsertAfterNode(Position pos, int coefficient, int exponent);
int AddPolynomials(Position head1, Position head2, Position resultHead);
int MultiplyPolynomials(Position head1, Position head2, Position resultHead);
int PrintPolynomial(char* name, Position firstNode);
int FreeMemory(Position head);


int main()
{
    Node head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
    Node head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
    Node sumResult = { .coefficient = 0, .exponent = 0, .next = NULL };
    Node multiplicationResult = { .coefficient = 0, .exponent = 0, .next = NULL };

    char fileName[MAX_LENGTH] = {0};
    EnterFileName(fileName);

    if(ReadFile(fileName, &head1, &head2) == EXIT_SUCCESS)
    {
        PrintPolynomial("1st polynomial: ", head1.next);
        PrintPolynomial("2nd polynomial: ", head2.next);

        AddPolynomials(&head1, &head2, &sumResult);
        MultiplyPolynomials(&head1, &head2, &multiplicationResult);

        PrintPolynomial("Addition: ", sumResult.next);
        PrintPolynomial("Multiplication: ", multiplicationResult.next);

        FreeMemory(&head1);
        FreeMemory(&head2);
        FreeMemory(&sumResult);
        FreeMemory(&multiplicationResult);
    }

    return EXIT_SUCCESS;
}



int EnterFileName(char* fileName)
{
    while(strlen(fileName) == 0)
    {
        printf("Enter the file name: ");
        scanf("%s", fileName);
    }

    return EXIT_SUCCESS;
}



int ReadFile(char* fileName, Position head1, Position head2)
{
    FILE* fp = NULL;
    char buffer[MAX_LENGTH] = {0};
    int flag = EXIT_SUCCESS;

    fp = fopen(fileName, "r");
    if(!fp)
    {
        perror("Can't open file!\n");
        return  EXIT_FAILURE;
    }



	fgets(buffer, MAX_LENGTH, fileName);
    //
    printf("DEBUG");
	flag = ParseStringIntoList(buffer, head1);
	if (flag != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LENGTH, fileName);
	flag = ParseStringIntoList(buffer,head2);
	if (flag != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

    fclose(fp);

    return EXIT_SUCCESS;
}



int ParseStringIntoList(char* buffer, Position head)
{
    int coefficient = 0;
    int exponent = 0;
    int flag = 0;
    int numOfBytes = 0;
    char* currentBuffer = buffer;
    Position newNode = NULL;

    while(strlen(currentBuffer) > 0)
    {
        flag = sscanf(currentBuffer, " %d %d %n", &coefficient, &exponent, &numOfBytes);
        if(flag != 2)
        {
            printf("Invalid file format!\n");
            return EXIT_FAILURE;
        }

        newNode = CreateNode(coefficient, exponent);
        if(!newNode)
        {
            return EXIT_FAILURE;
        }

        InsertSortedNode(head, newNode);
        currentBuffer += numOfBytes;
    }

    return EXIT_SUCCESS;
}



int DeleteAfterNode(Position prevNode)
{
    Position toDeleteNode = NULL;

    toDeleteNode = prevNode->next;
    prevNode->next = toDeleteNode->next;
    free(toDeleteNode);

    return EXIT_SUCCESS;
}



int InsertAfterNode(Position currentNode, Position newNode)
{
    newNode->next = currentNode->next;
    currentNode->next = newNode;

    return EXIT_SUCCESS;
}



int MergeNodes(Position currentNode, Position newNode)
{
    if(currentNode->next == NULL || !(currentNode->next->exponent == newNode->exponent))
    {
        InsertAfterNode(currentNode, newNode);
    }

    else
    {
        int sumOfCoefficients = currentNode->next->coefficient + newNode->coefficient;
        (sumOfCoefficients == 0 ? DeleteAfterNode(currentNode) : (currentNode->next->coefficient = sumOfCoefficients));
    }

    return EXIT_SUCCESS;
}



int InsertSortedNode(Position head, Position newNode)
{
    Position tempNode = head;

    while(tempNode->next != NULL && tempNode->next->exponent < newNode->exponent)
    {
        tempNode = tempNode->next;
    }

    MergeNodes(tempNode, newNode);

    return EXIT_SUCCESS;
}



Position CreateNode(int coefficient, int exponent)
{
    Position newNode = NULL;

    newNode = (Position)malloc(sizeof(Node));
    if(!newNode)
    {
        perror("Memory can't be allocated!\n");
        return newNode;
    }

    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;

    return newNode;
}



int PrintPolynomial(char* polynomialName, Position firstNode)
{
    printf(" %s = ", polynomialName);
    if(firstNode)
    {
        if(firstNode->exponent < 0)
        {
            (firstNode->coefficient == 1) ?
            printf("x^(%d)", firstNode->exponent) :
            printf("%dx^(%d)", firstNode->coefficient, firstNode->exponent);
        }

        else
        {
            (firstNode->coefficient == 1) ?
            printf("x^%d", firstNode->exponent) :
            printf("%dx^%d", firstNode->coefficient, firstNode->exponent);
        }

        firstNode = firstNode->next;
    }


    for(; firstNode != NULL; firstNode = firstNode->next)
    {
        if(firstNode->coefficient < 0)
        {
            (firstNode->exponent < 0) ?
            printf(" - %dx^(%d)", abs(firstNode->coefficient), firstNode->exponent) :
            printf(" - %dx^%d", abs(firstNode->coefficient), firstNode->exponent);
        }

        else
        {
            if(firstNode->exponent < 0)
            {
                (firstNode->coefficient == 1) ?
                printf(" + x^(%d)", firstNode->exponent) :
                printf(" + %dx^(%d)", firstNode->coefficient, firstNode->exponent);
            }

            else
            {
                (firstNode->coefficient == 1) ?
                printf(" + x^%d", firstNode->exponent) :
                printf(" + %dx^%d", firstNode->coefficient, firstNode->exponent);
            }
        }
    }

    printf("\n\n");

    return EXIT_SUCCESS;
}



int CreateAndInsertAfterNode(Position pos, int coefficient, int exponent)
{
    Position newNode = CreateNode(coefficient, exponent);
    if(!newNode)
    {
        return EXIT_FAILURE;
    }

    InsertAfterNode(pos, newNode);
    pos = pos->next;

    return EXIT_SUCCESS;
}



int AddPolynomials(Position head1, Position head2, Position resultHead)
{
    Position i = NULL;
    Position j = NULL;

    for(i = head1->next; i != NULL; i = i->next)
    {
        Position newNode = CreateNode(i->coefficient, i->exponent);
        if(!newNode)
        {
            return EXIT_FAILURE;
        }

        InsertSortedNode(resultHead, newNode);
    }

    for(j = head2->next; j != NULL; j = j->next)
    {
        Position newNode = CreateNode(j->coefficient, j->exponent);
        if(!newNode)
        {
            return EXIT_FAILURE;
        }

        InsertSortedNode(resultHead, newNode);
    }

    return EXIT_SUCCESS;
}



int MultiplyPolynomials(Position head1, Position head2, Position resultHead)
{
    Position i = NULL;
    Position j = NULL;

    for(i = head1->next; i != NULL; i = i->next)
    {
        for(j = head2->next; j != NULL; j = j->next)
        {
            Position newNode = CreateNode(i->coefficient * j->coefficient, i->exponent + j->exponent);
            if(!newNode)
            {
                return EXIT_FAILURE;
            }

            InsertSortedNode(resultHead, newNode);
        }
    }


    return EXIT_SUCCESS;
}



int FreeMemory(Position head)
{
    Position tempNode = head;

    while(tempNode->next)
    {
        DeleteAfterNode(tempNode);
    }

    return EXIT_SUCCESS;
}
