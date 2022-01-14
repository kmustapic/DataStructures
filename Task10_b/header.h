#ifndef HEADERFILE_H
#define HEADERFILE_H

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
CountryP FindCountry(CountryP currentCountry, char* countryName);
void FindCity(CountryP currentCountry, int minValue);
void ExecuteTask10_b();

#endif // HEADERFILE_H
