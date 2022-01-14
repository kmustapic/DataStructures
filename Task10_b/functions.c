#include <stdio.h>
#include <stdlib.h>
#include "header.h"

CountryP AddCountryToTree(CountryP rootNode, char* countryName, char* citiesFileName)
{
    CountryP newCountry = NULL;
    CityP currentCity = NULL;

    if(rootNode == NULL)
    {
        newCountry = (CountryP)malloc(sizeof(Country));
        if(newCountry == NULL)
        {
            perror("Memory is not allocated!\n");
            return NULL;
        }
        strcpy(newCountry->name, countryName);

        currentCity = (CityP)malloc(sizeof(City));
        if(currentCity == NULL)
        {
            perror("Memory is not allocated!\n");
            return NULL;
        }
        strcpy(currentCity->name, "");
        currentCity->population = 0;
        currentCity->next = NULL;
        newCountry->citiesP = currentCity;

        AddCitiesToList(newCountry->citiesP, citiesFileName);
        newCountry->left = NULL;
        newCountry->right = NULL;

        return newCountry;
    }
    else if(strcmp(rootNode->name, countryName) < 0)
    {
        rootNode->right = AddCountryToTree(rootNode->right, countryName, citiesFileName);
    }
    else if(strcmp(rootNode->name, countryName) > 0)
    {
        rootNode->left = AddCountryToTree(rootNode->left, countryName, citiesFileName);
    }

    return rootNode;
}

void AddCitiesToList(CityP headCityEl, char* citiesFileName)
{
    CityP newCity = NULL;
    FILE* fp = NULL;
    char cityName[MAX_SIZE];
    char buffer[MAX_SIZE];
    int numOfLines = 0;
    int population = 0;
    //CityP prevCity = headCityEl;
    CityP initialCity = headCityEl;

    fp = fopen(citiesFileName, "r");
    if(fp == NULL)
    {
        perror("File can't be opened!\n");
        return;
    }
    while(fgets(buffer, MAX_SIZE, fp))
    {
        numOfLines++;
    }
    rewind(fp);
    for(int i = 0; i < numOfLines; i++)
    {
        //prevCity = initialCity;
        headCityEl = initialCity;

        fscanf(fp, "%s %d", cityName, &population);
        newCity = (CityP)malloc(sizeof(City));
        if(newCity == NULL)
        {
            perror("Memory is not allocated!\n");
            return;
        }
        strcpy(newCity->name, cityName);
        newCity->population = population;

        /*
        // Cities sorted: HIGHEST population -> LOWEST population
        while(headCityEl != NULL)
        {
            if(headCityEl->next == NULL)
            {
                newCity->next = headCityEl->next;
                headCityEl->next = newCity;
                break;
            }
            if(CompareCityData(newCity, prevCity->next) == 1)
            {
                newCity->next = prevCity->next;
                prevCity->next = newCity;
                break;
            }

            prevCity = headCityEl;
            headCityEl = headCityEl->next;
        }
        */

        // Cities sorted: LOWEST population -> HIGHEST population
        while(headCityEl != NULL)
        {
            if(headCityEl->next == NULL)
            {
                headCityEl->next = newCity;
                newCity->next = NULL;
                break;
            }
            if(CompareCityData(newCity, headCityEl->next->name) == -1)
            {
                newCity->next = headCityEl->next;
                headCityEl->next = newCity;
                break;
            }
            headCityEl = headCityEl->next;
        }
    }
    fclose(fp);

    return;
}

int CompareCityData(CityP newCity, CityP existingCity)
{
    if(newCity->population > existingCity->population)
    {
        return 1;
    }
    else if(newCity->population < existingCity->population)
    {
        return -1;
    }
    else
    {
        if(strcmp(newCity->name, existingCity->name) >= 0)
        {
            return 1;
        }
        else if(strcmp(newCity->name, existingCity->name) < 0)
        {
            return -1;
        }
    }

    return EXIT_SUCCESS;
}

void PrintCountries(CountryP currentCountry)
{
    if(currentCountry == NULL)
    {
        return;
    }
    PrintCountries(currentCountry->left);
    printf("\n\t> %s\n", currentCountry->name);
    PrintCities(currentCountry->citiesP->next);
    PrintCountries(currentCountry->right);
}

void PrintCities(CityP currentCity)
{
    if(currentCity == NULL)
    {
        return;
    }
    while(currentCity != NULL)
    {
        printf("\t\t|__ %s\t%10d\n", currentCity->name, currentCity->population);
        currentCity = currentCity->next;
    }
}

CountryP FindCountry(CountryP currentCountry, char* countryName)
{
        if(currentCountry == NULL)
        {
            return NULL;
        }
        else if(strcmp(countryName, currentCountry->name) == 0)
        {
            return currentCountry;
        }
        else if(strcmp(countryName, currentCountry->name) < 0)
        {
            return FindCountry(currentCountry->left, countryName);
        }
        else if(strcmp(countryName, currentCountry->name) > 0)
        {
            return FindCountry(currentCountry->right, countryName);
        }
}

void FindCity(CountryP currentCountry, int minValue)
{
    CityP currentCity = currentCountry->citiesP;
    int flag = EXIT_FAILURE;

    if(currentCity == NULL)
    {
        printf("In country %s none cities are enetered!\n");
        return;
    }
    currentCity = currentCity->next;
    while(currentCity != NULL)
    {
        if(currentCity->population >= minValue)
        {
            printf("\t\t|__ %s\t%10d\n", currentCity->name, currentCity->population);
            flag = EXIT_SUCCESS;
        }
        currentCity = currentCity->next;
    }
    if(flag == EXIT_FAILURE)
    {
        printf("Cities in %s that have population greater than %d are not entered yet!", currentCountry->name, minValue);
    }
}

void ExecuteTask10_b()
{
    CountryP rootNode = NULL;
    FILE* fp = NULL;
    char countryName[MAX_SIZE];
    char citiesFileName[MAX_SIZE];
    int numOfLines = 0;
    char buffer[MAX_SIZE];
    CountryP foundCountry = NULL;
    int minValue = 0;

    fp = fopen("countries.txt", "r");
    if(fp == NULL)
    {
        perror("File can't be opened!\n");
        return EXIT_FAILURE;
    }
    while(fgets(buffer, MAX_SIZE, fp))
    {
        numOfLines++;
    }
    if(numOfLines-1 == 0)
    {
        perror("File that contains country names is empty!\n");
        return EXIT_FAILURE;
    }

    rewind(fp);
    for(int i = 0; i < numOfLines; i++)
    {
        fscanf(fp, "%s %s", countryName, citiesFileName);
        rootNode = AddCountryToTree(rootNode, countryName, citiesFileName);
    }
    fclose(fp);

    printf("___________________________________________________________________\n");
    printf("\t\tList of countries\n");
    printf("___________________________________________________________________\n");
    PrintCountries(rootNode);

    printf("___________________________________________________________________\n");
    printf("Enter country name that you want to search: ");
    scanf("%s", countryName);
    foundCountry = FindCountry(rootNode, countryName);
    while(foundCountry == NULL)
    {
        printf("That country isn't entered in the text file yet!\nTry again :)\n");
        sleep(3);
        system("cls");
        PrintCountries(rootNode);
        printf("___________________________________________________________________\n");
        printf("Enter country name that you want to search: ");
        scanf("%s", countryName);
        foundCountry = FindCountry(rootNode, countryName);
    }

    printf("___________________________________________________________________\n");
    printf("Enter minimum population value in %s you want to check out:  ", countryName);
    scanf("%d", &minValue);
    printf("___________________________________________________________________\n");
    printf("Cities in %s that have population more than %d habitants: \n\n", countryName, minValue);
    FindCity(foundCountry, minValue);
    printf("\n___________________________________________________________________\n");
}
