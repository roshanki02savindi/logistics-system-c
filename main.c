#include <stdio.h>

int main() {
    int choice;

    while (1) {
        printf("\n=== Logistics Management System ===\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Vehicle Management\n");
        printf("4. Delivery Request\n");
        printf("5. Reports\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("City Management selected.\n");
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
