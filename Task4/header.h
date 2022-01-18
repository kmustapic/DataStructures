#ifndef HEADERFILE_H
#define HEADERFILE_H

#define MAX_SIZE 1025

struct _polynomial;
typedef struct _polynomial* PolynomialP;
typedef struct _polynomial
{
    int coefficient;
    int exponent;
    PolynomialP next;
} Polynomial;

int ReadFile(char* fileName, PolynomialP headEl1, PolynomialP headEl2);
int ParseStringIntoList(char* buffer, PolynomialP headEl);
PolynomialP CreateEl(int coefficient, int exponent);
int InsertSortedEl(PolynomialP headEl, PolynomialP newEl);
int InsertAfterEl(PolynomialP headEl, PolynomialP newEl);
int DeleteAfterEl(PolynomialP prevEl);
void AddPolynomials(PolynomialP headEl1, PolynomialP headEl2, PolynomialP resultPolynomial);
void MultiplyPolynomials(PolynomialP headEl1, PolynomialP headEl2, PolynomialP resultPolynomial);
void PrintPolynomials(char* textToPrint, PolynomialP currentEl);

#endif
