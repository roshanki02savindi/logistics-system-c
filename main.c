#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define NAME_CITY 50
#define VH_TYPES 3
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310




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
void calDelivery(int source, int dest, int weight, int vhtype, char cities[MAX_CITIES][NAME_CITY]);
void printDeliveryReports(char cities[MAX_CITIES][NAME_CITY], int deliveryCount);
void findBestRoute(int path[], int start, int end, int *minDist, int bestPath[]);
void findLeastCostRoute(char cities[MAX_CITIES][NAME_CITY], int cityCount);
void displayPerformanceReport(char cities[MAX_CITIES][NAME_CITY], int deliveryCount);



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
        printf("6. Performance Report\n");
        printf("7. Save & Exit\n");
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
            deliveryRequest(cities,cityCount);
            break;
        case 5:
            printDeliveryReports(cities,deliveryCount);
            findLeastCostRoute(cities, cityCount);
            break;
        case 6:
            displayPerformanceReport(cities,deliveryCount);
            break;
        case 7:
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
void calDelivery(int source, int dest, int weight, int vhtype, char cities[MAX_CITIES][NAME_CITY])
{
    int dist = distances[source][dest];

    float baseCost = dist * vehicleRate[vhtype] * (1 + (float)weight / 10000);
    float fuelUsed = (float)dist / vehicleFuel[vhtype];
    float fuelCost = fuelUsed * FUEL_PRICE;
    float totalCost = baseCost + fuelCost;
    float profit = baseCost * 0.25;
    float customerCharge = totalCost + profit;
    float time = (float)dist / vehicleSpeed[vhtype];

    printf("\n =====================================================\n");
    printf("  DELIVERY COST ESTIMATION  ");
    printf("------------------------------------------------------\n");
    printf("From : %s\n", cities[source]);
    printf("To: %s\n", cities[dest]);
    printf("Minimum Distance: %d km\n", dist);
    printf("Vehicle: %s\n", vehicleNames[vhtype]);
    printf("Weight: %d kg\n", weight);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %d × %d × (1 + %d/10000) = %.2f LKR\n",
           dist, vehicleRate[vhtype], weight, baseCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customerCharge);
    printf("Estimated Time: %.2f hours\n", time);
    printf("======================================================\n");
}

void printDeliveryReports(char cities[MAX_CITIES][NAME_CITY], int deliveryCount)
{
    if (deliveryCount == 0)
    {
        printf("\n Delivery Record Not Found \n");
        return;
    }

    printf("\n===========================================================================================\n");
    printf("                    DELIVERY REPORTS                  \n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("%-5s %-15s %-15s %-10s %-10s %-10s %-10s\n",
           "No", "From", "To", "Dist(km)", "Cost(LKR)", "Profit", "Charge");
    printf("--------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < deliveryCount; i++)
    {
        int src = deliverySource[i];
        int dst = deliveryDestination[i];
        int wt = deliveryWeight[i];
        int vtype = deliveryVehicle[i];
        int dist = distances[src][dst];

        float baseCost = dist * vehicleRate[vtype] * (1 + (float)wt / 10000);
        float fuelUsed = (float)dist / vehicleFuel[vtype];
        float fuelCost = fuelUsed * FUEL_PRICE;
        float totalCost = baseCost + fuelCost;
        float profit = baseCost * 0.25;
        float customerCharge = totalCost + profit;

        printf("%-5d %-15s %-15s %-10d %-10.2f %-10.2f %-10.2f\n",
               i + 1, cities[src], cities[dst], dist, totalCost, profit, customerCharge);
    }

    printf("=============================================================================================\n");
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int totalDistance(int path[], int count) {
    int total = 0;
    for (int i = 0; i < count - 1; i++) {
        total += distances[path[i]][path[i + 1]];
    }
    return total;
}

void findBestRoute(int path[], int start, int end, int *minDist, int bestPath[]) {
    if (start == end) {
        int dist = totalDistance(path, end + 1);
        if (dist < *minDist) {
            *minDist = dist;
            for (int i = 0; i <= end; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    for (int i = start; i <= end; i++) {
        swap(&path[start], &path[i]);
        findBestRoute(path, start + 1, end, minDist, bestPath);
        swap(&path[start], &path[i]);
    }
}

void findLeastCostRoute(char cities[MAX_CITIES][NAME_CITY], int cityCount) {
    if (cityCount < 2) {
        printf("Add 2 cities to find the shortest route.\n");
        return;
    }

    int start, end;
    displayCities(cities, cityCount);

    printf("Enter Start City: ");
    scanf("%d", &start);
    printf("Enter Destination City: ");
    scanf("%d", &end);

    if (start < 1 || start > cityCount || end < 1 || end > cityCount || start == end) {
        printf("Invalid!\n");
        return;
    }

    int citySubset = (cityCount > 4) ? 4 : cityCount;
    int path[4], bestPath[4];
    for (int i = 0; i < citySubset; i++)
        path[i] = i;

    int minDist = INT_MAX;
    findBestRoute(path, 0, citySubset - 1, &minDist, bestPath);

    printf("\n===========================================\n");
    printf(" LEAST COST ROUTE INFORMATION\n");
    printf("------------------------------------------\n");
    printf("From: %s\n", cities[start - 1]);
    printf("To: %s\n", cities[end - 1]);
    printf("Minimum Distance: %d km\n", minDist);
    printf("Best Path: ");
    for (int i = 0; i < citySubset; i++) {
        printf("%s", cities[bestPath[i]]);
        if (i < citySubset - 1)
            printf(" ---> ");
    }
    printf("\n==========================================\n");
}


void displayPerformanceReport(char cities[MAX_CITIES][NAME_CITY], int deliveryCount)
{
    if (deliveryCount == 0)
    {
        printf("\n No delivery records found!\n");
        return;
    }

    float totalDistance = 0, totalProfit = 0, totalCharge = 0, totalTime = 0;
    int longest = 0, shortest = INT_MAX, longIndex = 0, shortIndex = 0;

    for (int i = 0; i < deliveryCount; i++)
    {
        int src = deliverySource[i];
        int dst = deliveryDestination[i];
        int wt = deliveryWeight[i];
        int vtype = deliveryVehicle[i];
        int dist = distances[src][dst];

        float baseCost = dist * vehicleRate[vtype] * (1 + (float)wt / 10000);
        float fuelUsed = (float)dist / vehicleFuel[vtype];
        float fuelCost = fuelUsed * FUEL_PRICE;
        float totalCost = baseCost + fuelCost;
        float profit = baseCost * 0.25;
        float customerCharge = totalCost + profit;
        float time = (float)dist / vehicleSpeed[vtype];

        totalDistance += dist;
        totalProfit += profit;
        totalCharge += customerCharge;
        totalTime += time;

        if (dist > longest) { longest = dist; longIndex = i; }
        if (dist < shortest) { shortest = dist; shortIndex = i; }
    }

    printf("\n======================================================\n");
    printf("                PERFORMANCE REPORT                    \n");
    printf("========================================================\n");
    printf("Total Deliveries Completed : %d\n", deliveryCount);
    printf("Total Distance Covered     : %.2f km\n", totalDistance);
    printf("Average Delivery Time      : %.2f hours\n", totalTime / deliveryCount);
    printf("Total Revenue Earned       : %.2f LKR\n", totalCharge);
    printf("Total Profit               : %.2f LKR\n", totalProfit);
    printf("--------------------------------------------------------\n");
    printf("Longest Route  : %s -> %s (%d km)\n",
           cities[deliverySource[longIndex]], cities[deliveryDestination[longIndex]], longest);
    printf("Shortest Route : %s -> %s (%d km)\n",
           cities[deliverySource[shortIndex]], cities[deliveryDestination[shortIndex]], shortest);
    printf("======================================================\n");
}









