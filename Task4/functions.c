#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int ReadFile(char *fileName, PolynomialP headEl1, PolynomialP headEl2)
{
    FILE *fp = NULL;
    char buffer[MAX_SIZE] = "";
    int flag = EXIT_SUCCESS;

    fp = fopen(fileName, "r");
    if(!fp)
    {
        perror("Can't open file!\n");
        return  EXIT_FAILURE;
    }
    fgets(buffer, MAX_SIZE, fp);
	flag = ParseStringIntoList(buffer, headEl1);
	if (flag != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_SIZE, fp);
	flag = ParseStringIntoList(buffer,headEl2);
//need to fix LOGICAL ERR in ParseStringIntoList!
printf("\nFINAL FLAG: %d\n", flag);
//check below
flag = EXIT_SUCCESS;
	if (flag != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

    fclose(fp);

    return EXIT_SUCCESS;
}

int ParseStringIntoList(char *buffer, PolynomialP headEl)
{
    //
    int i = 0;
    //

    int coefficient = 0;
    int exponent = 0;
    int flag = EXIT_SUCCESS;
    int numOfBytes = 0;
    char *currentBuffer = buffer;
    PolynomialP newEl = NULL;

    while(strlen(currentBuffer) > 0)
    {

//i++;
        flag = sscanf(currentBuffer, " %d %d %n", &coefficient, &exponent, &numOfBytes);
    //printf("\n__%d__%d__%d\n", coefficient, exponent, numOfBytes);

        if(flag != 2 )
        {
            printf("Invalid file format!\n");
            return EXIT_FAILURE;
        }
        newEl = CreateEl(coefficient, exponent);
        if(!newEl)
        {
            return EXIT_FAILURE;
        }
        InsertSortedEl(headEl, newEl);
        currentBuffer += numOfBytes;
    }

    return EXIT_SUCCESS;
}

PolynomialP CreateEl(int coefficient, int exponent)
{
    PolynomialP newEl = NULL;
    newEl = (PolynomialP)malloc(sizeof(Polynomial));
    if(!newEl)
    {
        printf("Memory can't be allocated!\n");
        return NULL;
    }
    newEl->coefficient = coefficient;
    newEl->exponent = exponent;
    newEl->next = NULL;

    return newEl;
}

int InsertSortedEl(PolynomialP headEl, PolynomialP newEl)
{
    PolynomialP tempEl = NULL;
    tempEl = (PolynomialP)malloc(sizeof(Polynomial));
    tempEl = headEl;

    if(newEl->coefficient != 0)
    {
        if(tempEl->next == NULL)
        {
            return InsertAfterEl(tempEl, newEl);
        }
        while(tempEl)
        {
            if(tempEl->next->exponent < newEl->exponent)
            {
                return InsertAfterEl(tempEl, newEl);
            }
            else if(tempEl->next->exponent == newEl->exponent)
            {
                if(tempEl->next->coefficient == -(newEl->coefficient))
                {
                    return DeleteAfterEl(tempEl);
                    tempEl->next->coefficient += newEl->coefficient;

                    return EXIT_SUCCESS;
                }
            }
            else if ((tempEl->next->next == NULL) && (tempEl->next->exponent > newEl->exponent))
            {
                return InsertAfterEl(tempEl->next, newEl);
            }
            tempEl = tempEl->next;
        }
    }
    return EXIT_SUCCESS;
}

int InsertAfterEl(PolynomialP headEl, PolynomialP newEl)
{
    newEl->next = headEl->next;
    headEl->next = newEl;

    return EXIT_SUCCESS;
}

int DeleteAfterEl(PolynomialP prevEl)
{
    PolynomialP toDelete = NULL;
    toDelete = (PolynomialP)malloc(sizeof(Polynomial));
    toDelete = prevEl->next;
    prevEl->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int AddPolynomials(PolynomialP headEl1, PolynomialP headEl2, PolynomialP resultPolynomial)
{
    PolynomialP newEl = NULL;
    newEl = (PolynomialP)malloc(sizeof(Polynomial));
    headEl1 = headEl1->next;
    headEl2 = headEl2->next;
    while(headEl1)
    {
        newEl = CreateEl(headEl1->coefficient, headEl1->exponent);
        if(!newEl)
        {
            printf("Element not created!\n");
            return EXIT_FAILURE;
        }
        InsertSortedEl(resultPolynomial, newEl);
        headEl1 = headEl1->next;
    }
    while(headEl2)
    {
        newEl = CreateEl(headEl2->coefficient, headEl2->exponent);
        if(!newEl)
        {
            printf("Element not created!\n");
            return EXIT_FAILURE;
        }
        InsertSortedEl(resultPolynomial, newEl);
        headEl2 = headEl2->next;
    }
}

int MultiplyPolynomials(PolynomialP headEl1, PolynomialP headEl2, PolynomialP resultPolynomial)
{
    int coefficient = 0, exponent = 0;
    PolynomialP i = NULL, j = NULL;
    PolynomialP newEl = NULL;

    i = (PolynomialP)malloc(sizeof(Polynomial));
    j = (PolynomialP)malloc(sizeof(Polynomial));
    newEl = (PolynomialP)malloc(sizeof(Polynomial));

    if(headEl1->next == NULL || headEl2->next == NULL)
    {
        return EXIT_FAILURE;
    }
    for(i = headEl1->next;i;i=i->next)
    {
        for(j = headEl2->next;j;j=j->next)
        {
            coefficient = i->coefficient * j->coefficient;
            exponent = i->exponent + j->exponent;
            newEl = CreateEl(coefficient, exponent);
            if(!newEl)
            {
                printf("Element not created!\n");
                return EXIT_FAILURE;
            }
            InsertSortedEl(resultPolynomial, newEl);
        }
    }
    return EXIT_SUCCESS;
}

//
void PrintPolynomial(char* textToPrint, PolynomialP currentEl)
{
    PolynomialP i = NULL;
    i = (PolynomialP)malloc(sizeof(Polynomial));
    if(!i)
    {
        printf("Memory not allocated!\n");
        return;
    }
    printf("%s", textToPrint);
    if(currentEl->next == NULL);
    {
        printf("0");

    }

    for(i = currentEl->next;i != NULL;i=i->next)
    {
        if(i->coefficient != 1 || i->exponent == 0)
        {
            if(i->coefficient > 0)
            {
                printf("%d", i->coefficient);
            }
            else
            {
                printf("(%d)", i->coefficient);
            }
        }
        if(i->exponent > 0)
        {
            printf("x^%d", i->exponent);
        }
        if(i->exponent < 0)
        {
            printf("x^(%d)", i->exponent);
        }
        if(i->next != NULL)
        {
            printf(" + ");
        }
    }
}
