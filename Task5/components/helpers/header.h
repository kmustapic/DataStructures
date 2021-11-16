#ifndef HEADERFILE_H
#define HEADERFILE_H

struct _StackNode;
typedef struct _StackNode *Position;
typedef struct _StackNode
{
    double number;
    Position next;
} StackNode;

Position CreateStackNode(double number);
int InsertAfterNode(Position head, Position newStackNode);
int Push(Position head, double number);
int Pop(Position head, double *res);
int DeleteAfterNode(Position pos);
int PerformOperation(Position head, char operation);
int CalculatePostfixFromFile(double *res, char *fileName);

#endif
