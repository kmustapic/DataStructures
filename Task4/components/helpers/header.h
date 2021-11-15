#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

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

#endif
