#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

struct _node;
typedef struct _node *NodeP;
typedef struct _node **NodePP;
typedef struct _node
{
    int data;
    NodeP left;
    NodeP right;
} Node;

NodeP CreateNewNode(int data);
NodeP CreateNewTree();
NodePP CreateQueue(int* front, int* rear);
void EnQueue(NodePP queue, int* rear, NodeP newNode);
NodeP DeQueue(NodePP queue, int* front);
void PrintLevelOrder(NodeP root);

#endif
