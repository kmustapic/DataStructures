#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101

static int flag = EXIT_FAILURE;

struct _city;
typedef struct _city* CityP;
struct _city
{
    char name[MAX_SIZE];
    int population;
    CityP left;
    CityP right;
} City;

struct _country;
typedef struct _country* CountryP;
struct _country
{
    char name[MAX_SIZE];
    CityP citiesP;
    CountryP next;
} Country;

void AddCountryToList(CountryP currentListEl, char* countryName, char* citiesFileName);
void AddCitiesToTree(CityP currentTreeNode, char* citiesFileName);
CityP AddCityToTree(CityP newCity, char* cityName, int population);
void PrintCountries(CountryP currentCountry);
void PrintCities(CityP currentCity);
CountryP FindCountry(CountryP currentCountry, char* countryName);
int FindCity(CityP currentCity, int minValue);

void AddCountryToList(CountryP currentListEl, char* countryName, char* citiesFileName)
{
    CountryP newListEl = NULL;
    CityP treeParentNode = NULL;

    newListEl = (CountryP)malloc(sizeof(Country));
    if(newListEl == NULL)
    {
        perror("Memory is not allocated!\n");
        return;
    }
    strcpy(newListEl->name, countryName);
    newListEl->citiesP = treeParentNode;

    treeParentNode = (CityP)malloc(sizeof(City));
    if(treeParentNode == NULL)
    {
        perror("Memory is not allocated!\n");
        return;
    }
    strcpy(treeParentNode->name, "");
    treeParentNode->population = 0;
    treeParentNode->left = NULL;
    treeParentNode->right = NULL;
    newListEl->citiesP = treeParentNode;
    AddCitiesToTree(newListEl->citiesP, citiesFileName);

    while(currentListEl != NULL)
    {
        if(currentListEl->next == NULL)
        {
            currentListEl->next = newListEl;
            newListEl->next = NULL;
            break;
        }
        if(strcmp(newListEl->name, currentListEl->next->name) < 0)
        {
            newListEl->next = currentListEl->next;
            currentListEl->next = newListEl;
            break;
        }
        currentListEl = currentListEl->next;
    }
}

void AddCitiesToTree(CityP currentTreeNode, char* citiesFileName)
{
    FILE* fp = NULL;
    char cityName[MAX_SIZE];
    int population = 0;

    fp = fopen(citiesFileName, "r");
    if(fp == NULL)
    {
        perror("File can't be opened!\n");
        return;
    }

    int numOfLines = 0;
    char buffer[MAX_SIZE];
    while(fgets(buffer, MAX_SIZE, fp))
    {
        numOfLines++;
    }
    rewind(fp);
    for(int i = 0; i < numOfLines; i++)
    {
        fscanf(fp, "%s %d", cityName, &population);
        currentTreeNode = AddCityToTree(currentTreeNode, cityName, population);
    }
    fclose(fp);

    return;
}

CityP AddCityToTree(CityP newCity, char* cityName, int population)
{
    CityP tempCityNode = NULL;
    if(newCity == NULL)
    {
        tempCityNode = (CityP)malloc(sizeof(City));
        if(tempCityNode == NULL)
        {
            perror("Memory is not allocated!\n");
            return NULL;
        }
        strcpy(tempCityNode->name, cityName);
        tempCityNode->population = population;
        tempCityNode->left = NULL;
        tempCityNode->right = NULL;

        return tempCityNode;
    }

    if(population < newCity->population)
    {
        newCity->left = AddCityToTree(newCity->left, cityName, population);
    }
    else if(population > newCity->population)
    {
        newCity->right = AddCityToTree(newCity->right, cityName, population);
    }
    else
    {
        if(strcmp(cityName, newCity->name) < 0)
        {
            newCity->left = AddCityToTree(newCity->left, cityName, population);
        }
        else
        {
            newCity->right = AddCityToTree(newCity->right, cityName, population);
        }
    }

    return newCity;
}

void PrintCountries(CountryP currentCountry)
{
    if(currentCountry == NULL)
    {
        perror("List of countries is empty!\n");
        return;
    }
    printf("___________________________________________________________________\n");
    printf("\t\tList of countries\n");
    printf("___________________________________________________________________\n\n");

    while(currentCountry != NULL)
    {
        printf("\t> %s\n", currentCountry->name);
        PrintCities(currentCountry->citiesP->right);
        currentCountry = currentCountry->next;
        printf("\n");
    }
}

void PrintCities(CityP currentCity)
{
    if(currentCity == NULL)
    {
        return;
    }
    PrintCities(currentCity->left);
    printf("\t\t|__ %s\n", currentCity->name);
    PrintCities(currentCity->right);
}

CountryP FindCountry(CountryP currentCountry, char* countryName)
{
    while(currentCountry != NULL)
    {
        if(strcmp(currentCountry->name, countryName) == 0)
        {
            return currentCountry;
        }
        currentCountry = currentCountry->next;
    }

    return currentCountry;
}

int FindCity(CityP currentCity, int minValue)
{
    if(currentCity == NULL)
    {
        return EXIT_FAILURE;
    }
    FindCity(currentCity->left, minValue);
    if(currentCity->population >= minValue)
    {
        flag = EXIT_SUCCESS;
        printf("\t\t|__ %s\t%d\n", currentCity->name, currentCity->population);
    }
    FindCity(currentCity->right, minValue);

    return EXIT_SUCCESS;
}

int main()
{
    struct _country head = {.name = "", .citiesP = NULL, .next = NULL } ;
    FILE* fp = NULL;
    char countryName[MAX_SIZE];
    char citiesFileName[MAX_SIZE];
    int numOfLines = 0;
    char buffer[MAX_SIZE];
    CountryP foundCountry = NULL;
    int minValue;

    fp = fopen("countries.txt", "r");
    if(fp == NULL)
    {
        perror("File can't be opened!\n");
        return EXIT_FAILURE;
    }
    /*
        If we just use condition like this:
        while(!feof(fp))
        { ... }
        the last (empty) line will be read, but will memorize
        last existing data, meaning last existing country will be
        "read twice".
        Explained here: https://stackoverflow.com/questions/30540804/program-reading-last-line-of-file-twice
        1 empty line is always added automatically when saving file.
        Be careful how many empty lines are left at the end of the document :)
    */
    while(fgets(buffer, MAX_SIZE, fp))
    {
        numOfLines++;
    }
    rewind(fp);
    for(int i = 0; i < numOfLines; i++)
    {
        fscanf(fp, "%s %s", countryName, citiesFileName);
        AddCountryToList(&head, countryName, citiesFileName);
    }
    fclose(fp);

    PrintCountries(head.next);

    printf("___________________________________________________________________\n");
    printf("Enter country name that you want to search: ");
    scanf("%s", countryName);
    foundCountry = FindCountry(head.next, countryName);
    while( foundCountry == NULL)
    {
        printf("That country doesn't exist in the list yet!\nTry again :)\n");
        sleep(3);
        system("cls");
        PrintCountries(head.next);
        printf("___________________________________________________________________\n");
        printf("Enter country name that you want to search: ");
        scanf("%s", countryName);
        foundCountry = FindCountry(head.next, countryName);
    }

    printf("___________________________________________________________________\n");
    printf("Enter minimum population value in %s you want to check out:  ", countryName);
    scanf("%d", &minValue);
    printf("___________________________________________________________________\n");
    printf("Cities in %s that has population more than %d habitants: \n\n", countryName, minValue);
    FindCity(foundCountry->citiesP, minValue);
    if(flag == EXIT_FAILURE)
    {
        printf("Cities in %s that have population greater than %d are not entered yet!", countryName, minValue);
    }
    printf("\n___________________________________________________________________\n");

    return EXIT_SUCCESS;
}
