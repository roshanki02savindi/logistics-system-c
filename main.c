#include <stdio.h>

#define MAX_CITIES 30
#define NAME_CITY 50
#define VH_TYPES 3
#define MAX_DELIVERIES 50



void cityManagement(char cities[MAX_CITIES][NAME_CITY], int *cityCount);
void addCity(char cities[MAX_CITIES][NAME_CITY], int *cityCount);
void renameCity(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void removeCity(char cities[MAX_CITIES][NAME_CITY], int *cityCount);
void displayCities(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void readLine(char text[], int size);
void vehicleManagement();
void deliveryRequest();

char cities[MAX_CITIES][NAME_CITY];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];
void distanceManagement(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void inputEditDistance(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void displayVehicleOption();
int deliverySource[MAX_DELIVERIES], deliveryDestination[MAX_DELIVERIES], deliveryWeight[MAX_DELIVERIES], deliveryVehicle[MAX_DELIVERIES];
int deliveryCount = 0;
int main()
{
    int choice;

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
            distanceManagement(cities, cityCount);
            break;
        case 3:
            vehicleManagement();
            displayVehicleOption();
            break;
        case 4:
            deliveryRequest();
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
    printf("City Removed Successfully!\n");
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

void distanceManagement(char cities[MAX_CITIES][NAME_CITY], int cityCount)
{
    int choice;

    do
    {
        printf("\n=== Distance Management ===\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            inputEditDistance(cities,cityCount);
            break;

        case 2:
            if (cityCount == 0)
            {
                printf("No cities to display. Please add cities first!\n");
                break;
            }
            printf("\n--- Distance Table ---\n");
            printf("%-15s","");
            for (int i = 0; i < cityCount; i++)
                printf("%-15s", cities[i]);
            printf("\n");

            for (int i = 0; i < cityCount; i++)
            {
                printf("%-15s", cities[i]);
                for (int j = 0; j < cityCount; j++)

                    printf("%-15d", distances[i][j]);
                printf("\n");
            }
            break;

        case 3:
            printf("Back to Main Menu...\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    while (choice != 3);
}
void inputEditDistance(char cities[MAX_CITIES][NAME_CITY], int cityCount)
{
    if(cityCount < 2)
    {
        printf("At least add 2 cities.\n");
        return;
    }

    int from, to, dist;
    displayCities(cities,cityCount);

    printf("From city number: ");
    scanf("%d", &from);
    printf("To city number: ");
    scanf("%d", &to);

    if(from < 1 || from > cityCount || to < 1 || to > cityCount || from == to)
    {
        printf("Invalid city numbers!\n");
        return;
    }

    printf("Enter distance (km): ");
    scanf("%d", &dist);

    distances[from-1][to-1] = dist;
    distances[to-1][from-1] = dist;
    printf("Distance updated Successfully..!\n");

}

char vehicleNames[VH_TYPES][20] = {"Van","Truck","Lorry"};
int vehicleRate[VH_TYPES] = {30,40,50};
int vehicleCapacity[VH_TYPES] = {1000, 5000, 10000};
int vehicleSpeed[VH_TYPES] = {60, 80, 100};
int vehicleFuel[VH_TYPES] = {12, 6, 4};

void vehicleManagement()
{
    printf("              VEHICLE MANAGEMENT TABLE\n");
    printf("------------------------------------------------------------\n");
    printf("%-10s %-15s %-15s %-15s %-10s\n",
           "Type", "Capacity(kg)", "Rate/km(LKR)", "Speed(km/h)", "Fuel(km/l)");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < VH_TYPES; i++)
    {
        printf("%-10s %-15d %-15d %-15d %-10d\n",
               vehicleNames[i], vehicleCapacity[i],
               vehicleRate[i], vehicleSpeed[i], vehicleFuel[i]);
    }

    printf("------------------------------------------------------------\n");
}

void displayVehicleOption()
{
    int select;

    printf("\n*** Choose Your Vehicle ***\n");
    for (int i = 0; i < VH_TYPES; i++)
    {
        printf("%d: %s\n", i + 1, vehicleNames[i]);
    }

    printf("Enter your Vehicle choice: ");
    scanf("%d", &select);

    if (select < 1 || select > VH_TYPES)
    {
        printf("Not a valid option.\n");
        return;
    }

    int index = select - 1;
    printf("\n+++ Vehicle Information +++\n");
    printf("TYPE: %s\n", vehicleNames[index]);
    printf("Capacity: %d kg\n", vehicleCapacity[index]);
    printf("Rate per km: %d LKR\n", vehicleRate[index]);
    printf("Average Speed: %d km/h\n", vehicleSpeed[index]);
    printf("Fuel Efficiency: %d km/l\n", vehicleFuel[index]);
}

void deliveryRequest()
{

    if(cityCount < 2)
    {
        printf("Add at least 2 cities before to create a delivery request.\n");
        return;
    }
    if(deliveryCount >= MAX_DELIVERIES)
    {
        printf("Maximum delivery limit reached!\n");
        return;
    }

    int source, dest, weight, vhtype;
     displayCities(cities,cityCount);

    printf("Enter start city number: ");
    scanf("%d", &source);
    printf("Enter destination city number: ");
    scanf("%d", &dest);
    if(source < 1 || source > cityCount || dest < 1 || dest > cityCount || source == dest)
    {
        printf("Invalid start or destination city!\n");
        return;
    }

    printf("Enter package weight in Kg: ");
    scanf("%d", &weight);

    displayVehicleOption();
    printf("Enter vehicle number: ");
    scanf("%d", &vhtype);
    if(vhtype < 1 || vhtype > VH_TYPES)
    {
        printf("Invalid vehicle selection!\n");
        return;
    }
    if(weight > vehicleCapacity[vhtype-1])
    {
        printf("Weight exceeds selected vehicle capacity!\n");
        return;
    }

    deliverySource[deliveryCount] = source - 1;
    deliveryDestination[deliveryCount] = dest - 1;
    deliveryWeight[deliveryCount] = weight;
    deliveryVehicle[deliveryCount] = vhtype - 1;
    deliveryCount++;
    printf("Delivery Request Added successfully!\n");
}




