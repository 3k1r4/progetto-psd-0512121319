#include <stdio.h>
#include <stdlib.h>
#include "./planner/planner.h"

int main(void) {
    //for testing pourpose use getCurrentDateML() to set manualy the date
    today = getCurrentDateAT();
    Planner planner = openPlanner();
    if (planner == NULL) {
        printf("Error.\n");
        return 1;
    }
    
    int choice;
    do {
        clearScreen();
        printf("\n\n\t      --- Navigation menu ---\n");
        printf("\n\t        --- "); 
        printDate(today);
        printf(" ---\n\n");
        printf("1. Add a new task\n");
        printf("2. Update a task\n");
        printf("3. Delete a task\n");
        printf("4. Restore a task\n");
        printf("5. View the planner\n");
        printf("6. Clear the history\n");
        printf("7. View your progress\n");
        printf("8. View your weekly report\n");
        printf("0. Close the planner\n");
        printf("\n\n\t      -----------------------\n\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        // Esegui l'operazione choice
        switch (choice) {
            case 1: insert(planner); break;
            case 2: modifyTask(planner); break;
            case 3: deleteTask(planner); break;
            case 4: restoreExpiredTask(planner); break;
            case 5: printPlanner(planner); break;
            case 6: deleteHistory(planner); break;
            case 7: showTaskProgress(planner); break;
            case 8: weeklyReport(planner); break;
            case 0: closePlanner(planner); break;
            default: printf("Invalid choice. retry\n");
        }
    } while (choice != 0);

    return 0;
}

