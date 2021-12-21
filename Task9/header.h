#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

struct _node;
typedef struct _node* NodeP;
struct _node
{
    int data;
    NodeP left;
    NodeP right;
} Node;

struct _list;
typedef struct _list* ListP;
struct _list
{
    int el;
    ListP next;
} List;

NodeP InsertElement(NodeP currentNodeP, int data);
void PrintElements(NodeP currentNodeP, ListP lp);
int ReplaceElements(NodeP currentNodeP);
void PushElementToList(ListP lp, int el);
void WriteInFile(FILE* fp, ListP lp);
void ExecuteTask9_a();
void ExecuteTask9_b();

#endif
