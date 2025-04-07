#include "caseLogic.h"

#define BUFF_MAX 256

void handleAddMenu(List* cities) {
    char buffer[BUFF_MAX];
    printf("\n1. Add City\n2. Add Citizen\nChoice: ");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer

    if (choice == 1) { // Add City
        printf("City Name: ");
        fgets(buffer, BUFF_MAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        elmtAddress newCity = allocate(strdup(buffer)); // strdup directly
        newCity->pCitizen = (List*)malloc(sizeof(List));
        createList(newCity->pCitizen);

        printf("Insert Method (1=Front, 2=Rear, 3=Manual): ");
        int opt;
        scanf("%d", &opt);
        while (getchar() != '\n');

        switch(opt) {
            case 1: insFront(cities, newCity); break;
            case 2: insRear(cities, newCity); break;
            case 3:
                unsigned short pos;
                printf("Position: ");
                scanf("%hu", &pos);
                insManual(cities, newCity, pos);
                break;
            default:
                printf("Invalid option!\n");
                deallocate(newCity); // Frees strdup'd name and node
        }
    } 
    else if (choice == 2) { // Add Citizen
        if (listEmpty(*cities)) {
            printf("No cities exist!\n");
            return;
        }

        printf("Citizen Name: ");
        fgets(buffer, BUFF_MAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        elmtAddress newCitizen = allocate(strdup(buffer)); // strdup directly

        printf("Target City: ");
        fgets(buffer, BUFF_MAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        elmtAddress city = searchList(*cities, buffer); // Direct buffer use

        if (!city) {
            printf("City not found!\n");
            deallocate(newCitizen); // Free citizen node and name
            return;
        }

        printf("Insert Method (1=Front, 2=Rear, 3=Manual): ");
        int opt;
        scanf("%d", &opt);
        while (getchar() != '\n');

        switch(opt) {
            case 1: insFront(city->pCitizen, newCitizen); break;
            case 2: insRear(city->pCitizen, newCitizen); break;
            case 3:
                unsigned short pos;
                printf("Position: ");
                scanf("%hu", &pos);
                insManual(city->pCitizen, newCitizen, pos);
                break;
            default:
                printf("Invalid option!\n");
                deallocate(newCitizen);
        }
    }
}

void handleDeleteMenu(List* cities) {
    char buffer[BUFF_MAX];
    printf("\n1. Delete City\n2. Delete Citizen\nChoice: ");
    int choice;
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 1) { // Delete City
        printf("Delete Method (1=Front, 2=Rear, 3=Manual): ");
        int opt;
        scanf("%d", &opt);
        while (getchar() != '\n');

        switch(opt) {
            case 1: delFront(cities); break;
            case 2: delRear(cities); break;
            case 3:
                unsigned short pos;
                printf("Position: ");
                scanf("%hu", &pos);
                delManual(cities, pos);
                break;
            default:
                printf("Invalid option!\n");
        }
    } 
    else if (choice == 2) { // Delete Citizen
        printf("Target City: ");
        fgets(buffer, BUFF_MAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        elmtAddress city = searchList(*cities, buffer);

        if (!city || listEmpty(*city->pCitizen)) {
            printf("City not found or has no citizens!\n");
            return;
        }

        printf("Citizen Name: ");
        fgets(buffer, BUFF_MAX, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        elmtAddress citizen = searchList(*city->pCitizen, buffer);

        if (!citizen) {
            printf("Citizen not found!\n");
            return;
        }

        // Delete citizen
        List* citizens = city->pCitizen;
        elmtAddress prev = NULL, curr = citizens->front;
        while (curr && curr != citizen) {
            prev = curr;
            curr = curr->next;
        }
        if (prev) prev->next = curr->next;
        else citizens->front = curr->next;
        deallocate(curr);
    }
}

// Search Citizen (uses buffer directly)
void handleSearchCitizen(List cities) {
    char buffer[BUFF_MAX];
    printf("Target City: ");
    fgets(buffer, BUFF_MAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    elmtAddress city = searchList(cities, buffer);

    if (!city) {
        printf("City not found!\n");
        return;
    }

    printf("Citizen Name: ");
    fgets(buffer, BUFF_MAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    elmtAddress citizen = searchList(*city->pCitizen, buffer);

    printf(citizen ? "Found: %s\n" : "Not found!\n", citizen ? citizen->name : "");
}

// Display Citizens in City 
void handleDisplayCitizens(List cities) {
    char buffer[BUFF_MAX];
    printf("City Name: ");
    fgets(buffer, BUFF_MAX, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    elmtAddress city = searchList(cities, buffer);

    if (!city) {
        printf("City not found!\n");
        return;
    }

    printf("Citizens in %s: ", city->name);
    printList(*city->pCitizen);
}

// Display City and Citizen Count
void handleDisplayCount(List cities) {
    int cityCount = getTotalElmt(cities);
    int citizenCount = 0;
    elmtAddress currentCity = cities.front;
    while (currentCity) {
        citizenCount += getTotalElmt(*currentCity->pCitizen);
        currentCity = currentCity->next;
    }
    printf("Total Cities: %d\n", cityCount);
    printf("Total Citizens: %d\n", citizenCount);
}
