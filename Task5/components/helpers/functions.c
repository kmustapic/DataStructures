#include <stdio.h>
#include <stdlib.h>

Position CreateStackNode(double number)
{
    Position newStackNode = NULL;

    newStackNode = (Position)malloc(sizeof(StackNode));
    if(!newStackNode)
    {
        perror("Can't allocate memory!\n");
        return newStackNode;
    }

    newStackNode->number = number;
    newStackNode->next = NULL;

    return newStackNode;
}



int InsertAfterNode(Position head, Position newStackNode)
{
    newStackNode->next = head->next;
    head->next = newStackNode;

    return EXIT_SUCCESS;
}



int Push(Position head, double number)
{
    Position newStackNode = CreateStackNode(number);
    if(!newStackNode)
    {
        return EXIT_FAILURE;
    }

    InsertAfterNode(head, newStackNode);

    return EXIT_SUCCESS;
}



int DeleteAfterNode(Position pos)
{
    Position tempStackNode = pos->next;

    if(!tempStackNode)
    {
        return EXIT_SUCCESS;
    }

    pos->next = tempStackNode->next;
    free(tempStackNode);

    return EXIT_SUCCESS;
}



int Pop(Position head, double *res)
{
    Position firstNode = head->next;

    if(!firstNode)
    {
        perror("Postfix not valid! Please check your file again!\n");
        return EXIT_FAILURE;
    }

    *res = firstNode->number;
    DeleteAfterNode(head);

    return EXIT_SUCCESS;
}



int PerformOperation(Position head, char operation)
{
    double operand1 = 0;
    double operand2 = 0;
    int flag1 = 0;
    int flag2 = 0;
    double res = 0;

    flag1 = Pop(head, &operand1);
    if(flag1 != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    flag2 = Pop(head, &operand2);
    if(flag2 != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

      switch (operation)
    {
    case '+':
        res = operand1 + operand2;
        break;
    case '-':
        res = operand1 - operand2;
        break;
    case '*':
        res = operand1 * operand2;
        break;
    case '/':
        if (operand2 == 0)
        {
            printf("Cannot divide with zero\n");
            return EXIT_FAILURE;
        }
        res = operand1 / operand2;
        break;
    default:
        printf("This operation is not supported!\n");
        return EXIT_FAILURE;
    }

    Push(head, res);

    return EXIT_SUCCESS;
}



int CalculatePostfixFromFile(double *res, char *fileName)
{
    FILE *fp = NULL;
    int fileLength = 0;
    int size = 0;
    int flag = 0;
    char *buffer = NULL;
    char *currentBuffer = NULL;
    char operation = '0';
    double number = 0;

    StackNode head = {.number = 0, .next = NULL};
    Position pos = &head;

    fp = fopen(fileName, "rb");
    if (!fp)
    {
        perror("Can't open file!\n");
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    fileLength = ftell(fp);

    buffer = (char *)calloc(fileLength + 1, sizeof(char));

    if (!buffer)
    {
        perror("Can't allocate!\n");
        return EXIT_FAILURE;
    }

    rewind(fp);
    fread(buffer, sizeof(char), fileLength, fp);
    printf("|%s|\n\n", buffer);
    fclose(fp);

    currentBuffer = buffer;

    while (strlen(currentBuffer) > 0)
    {
        flag = sscanf(currentBuffer, " %lf %n", &number, &size);
        if (flag == 1)
        {
            Push(pos, number);
            currentBuffer += size;
        }
        else
        {
            sscanf(currentBuffer, " %c %n", &operation, &size);

            flag = PerformOperation(&head, operation);
            if (flag != EXIT_SUCCESS)
            {
                free(buffer);
                while (head.next)
                {
                    DeleteAfterNode(pos);
                }

                return EXIT_FAILURE;
            }

            currentBuffer += size;
        }
    }

    free(buffer);

    flag = Pop(pos, res);
    if (flag != EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    if (head.next != NULL)
    {
        printf("Postfix not valid! Please check your file! again\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
