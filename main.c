#include <stdio.h>

#define MAX_CITIES 30
#define NAME_CITY 50

void cityManagement(char cities[MAX_CITIES][NAME_CITY], int *cityCount);
void addCity(char cities[MAX_CITIES][NAME_CITY], int *cityCount);
void renameCity(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void removeCity(char cities[MAX_CITIES][NAME_CITY], int *cityCount);
void displayCities(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void readLine(char text[], int size);

int main()
{
    int choice;
    char cities[MAX_CITIES][NAME_CITY];
    int cityCount = 0;

    while (1)
    {
        printf("\n=== Logistics Management System ===\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Vehicle Management\n");
        printf("4. Delivery Request\n");
        printf("5. Reports\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            cityManagement(cities, &cityCount);
            break;
        case 2:
            printf("Distance Management selected.\n");
            break;
        case 3:
            printf("Vehicle Management selected.\n");
            break;
        case 4:
            printf("Delivery Request selected.\n");
            break;
        case 5:
            printf("Reports selected.\n");
            break;
        case 6:
            printf("Exiting program.\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

void cityManagement(char cities[MAX_CITIES][NAME_CITY], int *cityCount)
{
    int choice;
    do
    {
        printf("\n=== City Management ===\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Display Cities\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addCity(cities, cityCount);
            break;
        case 2:
            renameCity(cities, *cityCount);
            break;
        case 3:
            removeCity(cities, cityCount);
            break;
        case 4:
            displayCities(cities, *cityCount);
            break;
        case 5:
            printf("Returning to Main Menu... \n");
            break;
        default:
            printf("Invalid option! Try again.\n");
        }
    }
    while (choice != 5);
}

void readLine(char text[], int size)
{
    int i = 0;
    char ch;
    getchar();

    while (i < size - 1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF)
            break;
        text[i] = ch;
        i++;
    }
    text[i] = '\0';
}

void addCity(char cities[MAX_CITIES][NAME_CITY], int *cityCount)
{
    if (*cityCount >= MAX_CITIES)
    {
        printf("Max City limit reached!..\n");
        return;
    }
    printf("Enter city Name: ");
    readLine(cities[*cityCount], NAME_CITY);

    for (int i = 0; i < *cityCount; i++)
    {
        int same = 1, j = 0;
        while (cities[i][j] != '\0' || cities[*cityCount][j] != '\0')
        {
            if (cities[i][j] != cities[*cityCount][j])
            {
                same = 0;
                break;
            }
            j++;
        }
        if (same)
        {
            printf("That City already exists!\n");
            return;
        }
    }

    (*cityCount)++;
    printf("City Added Successfully!\n");
}

void renameCity(char cities[MAX_CITIES][NAME_CITY], int cityCount)
{
    if (cityCount == 0)
    {
        printf("No cities to Rename!\n");
        return;
    }
    displayCities(cities, cityCount);

    int index;
    printf("Enter city Number to Rename: ");
    scanf("%d", &index);

    if (index < 1 || index > cityCount)
    {
        printf("Invalid city number!\n");
        return;
    }

    printf("Enter New Name for city: ");
    readLine(cities[index - 1], NAME_CITY);

    printf("City Renamed Successfully!\n");
}
void removeCity(char cities[MAX_CITIES][NAME_CITY], int *cityCount)
{
    if (*cityCount == 0)
    {
        printf("No cities to Remove!\n");
        return;
    }

    displayCities(cities, *cityCount);

    int index;
    printf("Enter city number to remove: ");
    scanf("%d", &index);

    if (index < 1 || index > *cityCount)
    {
        printf("Invalid city number!\n");
        return;
    }

    for (int i = index - 1; i < *cityCount - 1; i++)
    {
        int j = 0;
        while (cities[i + 1][j] != '\0')
        {
            cities[i][j] = cities[i + 1][j];
            j++;
        }
        cities[i][j] = '\0';
    }

    (*cityCount)--;
    printf("City Removed Successfuly!\n");
}

void displayCities(char cities[MAX_CITIES][NAME_CITY], int cityCount)
{
    if (cityCount == 0)
    {
        printf("No cities added yet.\n");
        return;
    }

    printf("\n--- List of Cities ---\n");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%d. %s\n", i + 1, cities[i]);
    }
    printf("Total Cities: %d\n", cityCount);
}







