#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 21

struct _directory;
typedef struct _directory *DirectoryP;
typedef struct _directory
{
    char name[N];
    DirectoryP sibling;
    DirectoryP child;
} Directory;

DirectoryP AddNewDirectory(DirectoryP current, DirectoryP newDirectory);

DirectoryP AddNewDirectory(DirectoryP current, DirectoryP newDirectory)
{
    if(current == NULL)
    {
        return newDirectory;
    }

    if(strcmp(current->name, newDirectory->name) > 0)
    {
        newDirectory->sibling = current;
        return newDirectory;
    }

    else if(strcmp(current->name, newDirectory->name) < 0)
    {
        current->sibling = AddNewDirectory(current->sibling, newDirectory);
    }

    else
    {
        printf("That directory already exists!\n");
        free(newDirectory);
    }

    return current;
}


int main()
{
    int choice;

    printf("Chose an option from the menu:\n");
    switch(choice)
    {
    case 1:
        //AddNewDirectory
        break;
    case 2:
        //CreateNewSubDirectory
        break;
    case 3:
        //PrintDirectoryContent
        break;
    case 4:
        //GoBackToPreviousDirectory
        break;
    case 5:
        //Exit
        break;
    default:
        // error message
        break;
    }

    return 0;
}
