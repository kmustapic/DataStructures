#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>

struct _node;
typedef struct _node *NodeP;
typedef struct _node
{
    int data;
    NodeP left;
    NodeP right;
} Node;

void ExecuteTask8();
void PrintMenu();
NodeP CreateBST(NodeP root);
NodeP InsertNode(NodeP currentNodeP, int data);
void InsertTreeElement(NodeP root);
NodeP FindNode(NodeP currentNodeP, int data);
void FindTreeElement(NodeP root);
NodeP MinValueNode(NodeP currentDirP);
NodeP DeleteNode(NodeP currentNodeP, int data);
void DeleteTreeElement(NodeP root);
void PrintPreorder(NodeP currentNodeP);
void PrintInorder(NodeP currentNodeP);
void PrintPostorder(NodeP currentNodeP);
void BSTPrintout(NodeP root);
void ExitApp();

#endif
