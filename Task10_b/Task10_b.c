#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 101

struct _city;
typedef struct _city* CityP;
struct _city
{
    char name[MAX_SIZE];
    int population;
    CityP next;
} City;

struct _country;
typedef struct _country* CountryP;
struct _country
{
    char name[MAX_SIZE];
    CountryP left;
    CountryP right;
    CityP citiesP;
} Country;

CountryP AddCountryToTree(CountryP rootNode, char* countryName, char* citiesFileName);
void AddCitiesToList(CityP currentCity,char* citiesFileName);
int CompareCityData(CityP newCity, CityP nextCity);
void PrintCountries(CountryP currentCountry);
void PrintCities(CityP currentCity);

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
    CityP prevCity = headCityEl;
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
        prevCity = initialCity;
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

int main()
{
    CountryP rootNode = NULL;
    FILE* fp = NULL;
    char countryName[MAX_SIZE];
    char citiesFileName[MAX_SIZE];
    int numOfLines = 0;
    char buffer[MAX_SIZE];

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


    return EXIT_SUCCESS;
}
