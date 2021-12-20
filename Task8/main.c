#include <stdio.h>
#include <stdlib.h>

struct_node;
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

void ExecuteTask8()
{
    PrintMenu();

    int choice;
    NodeP root = NULL;
    root = CreateBST(root);

    while(EXIT_FAILURE)
    {
        system("cls");
        PrintMenu();

        printf("Chose an option: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice)
        {
        case 1:
            InsertTreeElement(root);
            break;
        case 2:
            BSTPrintout(root);
            break;
        case 3:
            DeleteTreeElement(root);
            break;
        case 4:
            FindTreeElement(root);
            break;
        case 5:
            ExitApp();
            return EXIT_SUCCESS;
        default:
            {
                printf("Entered option doesn't exist!\n");
                sleep(4);
            }
        }
    }
}

void PrintMenu()
{
    printf("=================================================================\n");
    printf("\t\tBinary Search Tree (BST)\n");
    printf("=================================================================\n");
    printf("Options available:\n");
    printf("\n\t\t1 - Insert a new element in BST");
    printf("\n\t\t2 - Print BST elements");
    printf("\n\t\t3 - Delete BST element");
    printf("\n\t\t4 - Find BST element");
    printf("\n\t\t5 - Exit application\n");
    printf("\n=================================================================\n\n");
}

NodeP CreateBST(NodeP root)
{
    int n,i,el;

    printf("Number of BST elements: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("(%d):  ", i+1);
        scanf("%d", &el);
        root = InsertNode(root, el);
    }

    return root;
}

NodeP InsertNode(NodeP currentNodeP, int data)
{
    NodeP p = NULL;
    if(currentNodeP == NULL)
    {
        p = (NodeP)malloc(sizeof(Node));
        p->data = data;
        p->left = p->right = NULL;

        return p;
    }

    else if(data < currentNodeP->data)
    {
        currentNodeP->left = InsertNode(currentNodeP->left, data);
    }

    else if(data > currentNodeP->data)
    {
        currentNodeP->right = InsertNode(currentNodeP->right, data);
    }

    return currentNodeP;
}

void InsertTreeElement(NodeP root)
{
    int el;
    printf("Element to insert: ");
    scanf("%d", &el);
    root = InsertNode(root, el);
}

NodeP FindNode(NodeP currentNodeP, int data)
{
    if(currentNodeP == NULL)
    {
        printf("Element (%d) doesn't exist!", data);
        sleep(4);
        return NULL;
    }

    else if(data < currentNodeP->data)
    {
        return FindNode(currentNodeP->left, data);
    }

    else if(data > currentNodeP->data)
    {
        return FindNode(currentNodeP->right, data);
    }

    return currentNodeP;
}

void FindTreeElement(NodeP root)
{
    int el;
    NodeP findNode = NULL;

    printf("Element to find: ");
    scanf("%d", &el);
    findNode = FindNode(root,el);
    if(findNode != NULL)
        {
            printf("Element (%d) exists.", el);
            sleep(4);
        }
}

NodeP MinValueNode(NodeP currentDirP)
{
    NodeP tempNode = currentDirP;
    while(tempNode && tempNode->left != NULL)
    {
        tempNode = tempNode->left;
    }

    return tempNode;
}

NodeP DeleteNode(NodeP currentNodeP, int data)
{
    NodeP tempNodeP = NULL;
    if(currentNodeP == NULL)
    {
        printf("That element doesn't exist!\n");
        sleep(4);
    }

    else if(data < currentNodeP->data)
    {
        currentNodeP->left = DeleteNode(currentNodeP->left, data);
    }

    else if(data > currentNodeP->data)
    {
        currentNodeP->right = DeleteNode(currentNodeP->right, data);
    }

    else
    {
        if(currentNodeP->left == NULL)
        {
            tempNodeP = currentNodeP->right;
            free(currentNodeP);

            return tempNodeP;
        }

        else if(currentNodeP->right == NULL)
        {
            tempNodeP = currentNodeP->left;
            free(currentNodeP);

            return tempNodeP;
        }

        tempNodeP = MinValueNode(currentNodeP->right);
        currentNodeP->data = tempNodeP->data;
        currentNodeP->right = DeleteNode(currentNodeP->right, tempNodeP->data);
    }

    return currentNodeP;
}

void DeleteTreeElement(NodeP root)
{
    int el;
    printf("Element to delete: ");
    scanf("%d", &el);
    root = DeleteNode(root,el);
}

void PrintPreorder(NodeP currentNodeP)
{
    if(currentNodeP == NULL)
    {
        return;
    }
    printf("%d ", currentNodeP->data);
    PrintPreorder(currentNodeP->left);
    PrintPreorder(currentNodeP->right);
}

void PrintInorder(NodeP currentNodeP)
{
    if(currentNodeP == NULL)
    {
        return;
    }
    PrintInorder(currentNodeP->left);
    printf("%d ", currentNodeP->data);
    PrintInorder(currentNodeP->right);
}

void PrintPostorder(NodeP currentNodeP)
{
    if(currentNodeP == NULL)
    {
        return;
    }
    PrintPostorder(currentNodeP->left);
    PrintPostorder(currentNodeP->right);
    printf("%d ", currentNodeP->data);
}

void BSTPrintout(NodeP root)
{
    printf("\> Preorder printout:  ");
    PrintPreorder(root);
    printf("\n> Inorder printout:   ");
    PrintInorder(root);
    printf("\n> Postorder printout: ");
    PrintPostorder(root);
    sleep(4);
}

void ExitApp()
{
    printf("You exited application!\n");
    sleep(3);
    return;
}

int main()
{
    ExecuteTask8();
    return EXIT_SUCCESS;
}
