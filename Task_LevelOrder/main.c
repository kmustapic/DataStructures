#include <stdio.h>
#include "header.h"

int main()
{
    NodeP root = CreateNewTree();
    PrintLevelOrder(root);

    return 0;
}
