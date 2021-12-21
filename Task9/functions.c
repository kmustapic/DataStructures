#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

NodeP InsertElement(NodeP currentNodeP, int data)
{
    NodeP p;
    if(currentNodeP == NULL)
    {
        p = (NodeP)malloc(sizeof(Node));
        p->data = data;
        p->left = NULL;
        p->right = NULL;

        return p;
    }
    if(data >= currentNodeP->data)
    {
        currentNodeP->right = InsertElement(currentNodeP->right, data);
    }

    if(data < currentNodeP->data)
    {
        currentNodeP->left = InsertElement(currentNodeP->left, data);
    }

    return currentNodeP;
}

void PrintElements(NodeP currentNodeP, ListP lp)
{
    if(currentNodeP == NULL)
        return;
    PrintElements(currentNodeP->right, lp);
    printf("%d ", currentNodeP->data);
    PushElementToList(lp ,currentNodeP->data);
    PrintElements(currentNodeP->left, lp);
}

int ReplaceElements(NodeP currentNodeP)
{
    int temp;
    if(currentNodeP == NULL)
    {
        return EXIT_SUCCESS;
    }

    temp = currentNodeP->data;
    currentNodeP->data = ReplaceElements(currentNodeP->left) + ReplaceElements(currentNodeP->right);
    return temp + currentNodeP->data;
}

void PushElementToList(ListP lp, int el)
{
    ListP p;
    while(lp != NULL)
    {
        if(lp->next == NULL)
        {
            p = (ListP)malloc(sizeof(List));
            p->el = el;
            lp->next = p;
            p->next = NULL;

            return;
        }
        lp = lp->next;
    }
}

void WriteInFile(FILE* fp, ListP lp)
{
    fp = fopen("printout", "w");
    while(fp != NULL)
    {
        fprintf(fp, "%d ", lp->el);
        lp = lp->next;
    }
    fprintf(fp, "\n");
    fclose(fp);
}


void ExecuteTask9_a()
{
    /*
    NodeP root;
    int elements[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};

    root->data = elements[0];
    root->left = NULL;
    root->right = NULL;

    for(int i = 1; i < 10; i++)
    {
       root = InsertElements(root, elements[i]);
    }

    //PrintElements(root);
    */
}

void ExecuteTask9_b()
{
    srand(time(NULL));
    NodeP root;
    int i, el;
    FILE* fp;

    // Declaration and initialization of head variable type List doesn't work via alias
    //  List head = {.el = 0, .next = NULL};

    struct _list head = {.el = 0, .next = NULL};

    root = (NodeP)malloc(sizeof(Node));
    root->data = rand() % 80 + 10;
    root->left = NULL;
    root->right = NULL;
    printf("%d ", root->data);

    for(i = 1; i < 10; i++)
    {
        el = rand() % 80 + 10;
        printf("%d ", el);
        root = InsertElement(root, el);
    }
    printf("\n");

    PrintElements(root, &head);
    WriteInFile(fp, head.next);

    root->data = ReplaceElements(root->left) + ReplaceElements(root->right);

    printf("\n");
    PrintElements(root, &head);

    WriteInFile(fp, head.next);
}

