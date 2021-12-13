#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define MAX_Q_SIZE 100

NodeP CreateNewNode(int data)
{
    NodeP newNode = (NodeP)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

NodeP CreateNewTree()
{
    NodeP root = CreateNewNode(1);

    root->left = CreateNewNode(2);
    root->right = CreateNewNode(3);

    root->left->left = CreateNewNode(4);
    root->left->right = CreateNewNode(5);
    root->right->left = CreateNewNode(6);
    root->right->right = CreateNewNode(7);

    root->left->left->left = CreateNewNode(8);
    root->left->left->right = CreateNewNode(9);
    root->left->right->left = CreateNewNode(10);

    return root;
}

NodePP CreateQueue(int* front, int* rear)
{
    NodePP queue = (NodePP)malloc(sizeof(NodeP)*MAX_Q_SIZE);
    *front = *rear = 0;

    return queue;
}

void EnQueue(NodePP queue, int* rear, NodeP newNode)
{
    queue[*rear] = newNode;
    (*rear)++;
}

NodeP DeQueue(NodePP queue, int* front)
{
    (*front)++;

    return queue[*front - 1];
}

void PrintLevelOrder(NodeP root)
{
    printf("Binary Tree Level Order Traversal: ");

    int rear, front;
    NodePP queue = CreateQueue(&front, &rear);
    NodeP tempNode = root;

    while(tempNode)
    {
        printf("%d ", tempNode->data);

        if(tempNode->left)
        {
            EnQueue(queue, &rear, tempNode->left);
        }

        if(tempNode->right)
        {
            EnQueue(queue, &rear, tempNode->right);
        }

        tempNode = DeQueue(queue, &front);
    }
}
