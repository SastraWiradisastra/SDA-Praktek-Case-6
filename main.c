#include "structure.h"
#include "caseLogic.h"

int main() {
    List cities;
    createList(&cities);
    int choice;

    do {
	printf("\n=== Main Menu ===\n");
	printf("1. Add City/Citizen\n");
	printf("2. Delete City/Citizen\n");
	printf("3. Search Citizen\n");
	printf("4. Display Citizens\n");
	printf("5. Display Totals\n");
	printf("6. Exit\n");
	printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer

        switch(choice) {
            case 1: handleAddMenu(&cities); break;
            case 2: handleDeleteMenu(&cities); break;
            case 3: handleSearchCitizen(cities); break;
            case 4: handleDisplayCitizens(cities); break;
            case 5: handleDisplayCount(cities); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    deleteList(&cities); // Cleanup all memory
    return 0;
}
