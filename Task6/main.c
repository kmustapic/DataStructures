#define _CRT_SECURE_NO_WARNINGS
#include "bill.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILE_NAME (1024)

int userSearchArticleInRange(BillP head);
int searchArticleInRange(BillP head, FilterP filter);

int main(int argc, char *argv[]) {
    Bill head;
    char fileName[MAX_FILE_NAME] = { 0 };
    int status = EXIT_SUCCESS;

    InitializeBill(&head);

    do {
        printf("Please insert filename ->\t");
        scanf(" %s", fileName);

        status = ReadBillsFromFile(&head, fileName);
    } while (status > EXIT_SUCCESS);
    if (status != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    printf("\r\n"
        "\t ** Successfully read %s:\r\n\r\n", fileName);
    PrintAllBills(&head);
    userSearchArticleInRange(&head);
    DeleteAllBills(&head);

    return EXIT_SUCCESS;
}

int userSearchArticleInRange(BillP head) {
    char article[MAX_ARTICLE_NAME] = { 0 };
    char dateFromString[MAX_DATE_AS_STRING] = { 0 };
    char dateToString[MAX_DATE_AS_STRING] = { 0 };
    FilterP filter = NULL;

    printf("\t ********* SEARCH **********\r\n");
    printf("\t <article> <from date> <to date> (inclusive)\r\n");
    printf("\t Example: kruh 1992-01-03 1992-02-08\r\n");

    do {
        printf("\t Your input: ");
        scanf(" %s %s %s", article, dateFromString, dateToString);

        filter = CreateFilter(dateFromString, dateToString, article);
    } while (!filter);

    searchArticleInRange(head, filter);
    DeleteFilter(filter);

    return EXIT_SUCCESS;
}

int searchArticleInRange(BillP head, FilterP filter) {
    BillP bill = NULL;
    int totalCount = 0;
    float totalPrice = 0.0f;

    printf("\t     Result:\r\n");

    for (bill = head->next; bill != NULL; bill = bill->next) {
        if (IsDateInsideOfRange(bill->date, filter->from, filter->to)) {
            ArticleP article = FindArticleByName(&bill->articleHead, filter->name);

            if (article) {
                printf("\t\t- ");
                PrintArticle(article);
                printf("\r\n");
                totalCount += article->count;
                totalPrice += article->count * article->price;
            }
        }
    }

    printf(
        "\t\tSearch result for \"%s\"\r\n"
        "\t\t\tCount:\t\t%d\r\n"
        "\t\t\tTotal profit\t%.02f\r\n",
        filter->name,
        totalCount,
        totalPrice
    );
}
