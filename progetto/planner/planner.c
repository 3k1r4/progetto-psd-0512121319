#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../char/char.h"
#include "../list/list.h"
#include "../pQueue/pQueue.h"
#include "planner.h"

struct planner {
    pQueue inProgress;
    list completed;
    list expired;
};

/* checkExpired
 * Syntax Specification:
 * bool checkExpired(Planner p);
 *
 * Semantic Specification:
 * Checks if any tasks in the in-progress queue have expired and moves them to the expired list.
 *
 * Preconditions:
 * - 'p' must be a valid Planner with a potentially non-empty in-progress queue.
 * - The global variable 'today' must contain a valid date string.
 *
 * Postconditions:
 * - Tasks that are past their deadline are moved from in-progress to expired.
 * - Returns true if at least one task was expired.
 *
 * Side Effects:
 * - Modifies the Planner's inProgress and expired lists.
 * - Prints messages to the terminal.
 */
bool checkExpired(Planner p) {
    if (emptyPQ(p->inProgress)) {
        printf("\nThe queue is empty or non-existent.\n");
        return false;
    }

    Task t;
    bool found = false;
    for(int i = 0; i < getSize(p->inProgress); i++) {
        t = getByIndex(p->inProgress, i);
        if (compareDates(getDeadline(t), today) < 0) {
            found = true;
            printf("\nTask '%s' expired", getTitle(t));
            p->expired = consList(pop(p->inProgress, t), p->expired);
            i--;
        }
    }
    if (emptyPQ(p->inProgress)) {
        printf("\nAll tasks have expired.\n");
    } else {
        printf("\nDeadline check completed\n");
    }
    return found;
}

/* generateWeeklyReport
 * Syntax Specification:
 * void generateWeeklyReport(Planner p);
 *
 * Semantic Specification:
 * Generates a weekly report file listing completed, in-progress, and expired tasks since the last Monday.
 *
 * Preconditions:
 * - 'p' must be a valid pointer to a Planner.
 * - The global variable 'today' must be initialized with a valid date.
 *
 * Postconditions:
 * - Appends a formatted report to the "./Data/report.txt" file.
 *
 * Side Effects:
 * - Writes to a file.
 * - Reads data from Planner and outputs messages in case of errors.
 */
void generateWeeklyReport(Planner p, char *monday) {
    FILE *reportFile = fopen("./Data/report.txt", "a"); // Apertura in modalità append per non sovrascrivere il contenuto
    int counter = 0;

    if (reportFile == NULL) {
        printf("\nError: Unable to open report file.\n");
        return;
    }

    fprintf(reportFile, "%s", today);
    fprintf(reportFile, "\n$\n\n\t      --- Weekly Report ---\n\n");

    if (p->completed != NULL) {
        fprintf(reportFile, "\n+ Completed tasks:\n");
        list temp = p->completed;
        while (temp != NULL) {
            Task t = getValue(temp);
            if (compareDates(getCompletionDate(t), monday) >= 0 && compareDates(getCompletionDate(t), today) <= 0) {
                fprintf(reportFile, "- %s (%s) Completed on: ", getTitle(t), getCourse(t));
                fprintDate(reportFile, getCompletionDate(t));
                fprintf(reportFile, "\n");
                counter++;
            }
            temp = getNext(temp);
        }
        fprintf(reportFile, "* There are %s completed task", counter ? intToString(counter) : "no" );
    }

    if (p->inProgress != NULL) {
        counter = 0;
        fprintf(reportFile, "\n\n+ Tasks in progress:\n");
        for (int i = 0; i < getSize(p->inProgress); i++, counter++) {
            Task t = getByIndex(p->inProgress, i);
            if (compareDates(getDeadline(t), today) == 0) {
            fprintf(reportFile, "- %s (%s) ! Due today !\n", getTitle(t), getCourse(t));
            return;
            }

            fprintf(reportFile, "- %s (%s) Deadline: ", getTitle(t), getCourse(t));
            fprintDate(reportFile, getDeadline(t));
            fprintf(reportFile, "\n");
        }
        fprintf(reportFile, "* There are %s in progress task", counter ? intToString(counter) : "no" );
    }

    if (p->expired != NULL) {
        counter = 0;
        fprintf(reportFile, "\n\n+ Expired tasks:\n");
        list temp = p->expired;
        while (temp != NULL) {
            Task t = getValue(temp);
            if (compareDates(getDeadline(t), monday) >= 0 && compareDates(getDeadline(t), today) < 0) {
                fprintf(reportFile, "- %s (%s) Expired on: ", getTitle(t), getCourse(t));
                fprintDate(reportFile, getDeadline(t));
                fprintf(reportFile,"\n");
                counter++;
            }
            temp = getNext(temp);
        }
        fprintf(reportFile, "* There are %s expired task", counter ? intToString(counter) : "no" );
    }

    fprintf(reportFile, "\n\n\t      ---------------------\n\n$\n");

    fclose(reportFile); // Chiude il file dopo aver scritto il report
}

Planner openPlanner() {
    Planner p = malloc(sizeof(struct planner));
    if (p != NULL) {
        p->inProgress = newPQ();
        p->completed = newList();
        p->expired = newList();

        if (p->inProgress == NULL || p->completed != NULL || p->expired != NULL) {
            printf("Memory allocation error for planner internal structures.\n");
            free(p);
            return NULL;
        }

        scanFileQueue(p->inProgress, fopen("./Data/progress.txt", "r"));
        p->completed = scanFileList(p->completed, fopen("./Data/completed.txt", "r"));
        p->expired = scanFileList(p->expired, fopen("./Data/expired.txt", "r"));
        checkExpired(p);
        if (compareDates(today, getPreviousMonday()) == 0){
            char *monday = getLastWeekDate();
            generateWeeklyReport(p, monday);
        }

    } else {
        printf("Memory allocation error for planner.\n");
    }
    return p;
}

int closePlanner(Planner p){
    if (p == NULL) {
        printf("\nError: planner is empty or non-existent\n");
        return 0;
    }

    saveOnFileQueue(p->inProgress, "./Data/progress.txt");
    saveOnFileList(p->completed, "./Data/completed.txt");
    saveOnFileList(p->expired, "./Data/expired.txt");

    freePQ(p->inProgress);
    freeList(&(p->completed));
    freeList(&(p->expired));
    free(p);
    printf("\n--- Study session ended ---\n");
}

/* setCompleted
 * Syntax Specification:
 * int setCompleted(Task t, Planner p);
 *
 * Semantic Specification:
 * Marks a given task as completed by setting its percentage to 100 and setting its completion date.
 *
 * Preconditions:
 * - 't' must be a valid Task.
 * - 'p' must be a valid Planner.
 * - The global variable 'today' must contain a valid date string.
 *
 * Postconditions:
 * - The task is updated as completed.
 * - The task is moved from the in-progress list to the completed list.
 *
 * Side Effects:
 * - Modifies task attributes.
 * - Changes Planner state.
 * - Prints messages to the terminal.
 */
int setCompleted(Task t, Planner p){ 
    if (t == NULL) {
        printf("\nError: task is empty or non-existent\n");
        return 0;
    }

    if (strcmp(getCompletionDate(t), "00000000") != 0) {
        printf("\nTask is already completed.\n");
    } else {
        setCompletionPercentage(t, 100.0);
        t = setCompletionDate(t, today);
        p->completed = consList(pop(p->inProgress, t), p->completed);
        printf("\nTask '%s' successfully completed.\n", getTitle(t));
    }

    return 1;
}

int restoreExpiredTask(Planner p) {
    if (p->inProgress == NULL || p->expired == NULL ) {
        printf("\nError: the queue or the list is empty or non-existent\n");
        return 0;
    }
    char title[21];
    clearBuffer();
    printf("\nEnter the title of the task to restore: ");
    read(20, title);

    clearScreen();
    printf("\n\n      --- Restore Expired Task ---\n\n");
    Task t = getByLTitle(p->expired, title);
    if (t != NULL) {
        t = setCompletionPercentage(t, 0.0);
        char pTxt[7];
        char newDeadline[9];
        strcpy(newDeadline, "00000000");
        t = setStartDate(t);

        while (1) {
            printf("\nEnter the priority level (low/medium/high): ");
            read(6, pTxt);

            if ((strcmp(pTxt, "low") == 0) || (strcmp(pTxt, "medium") == 0) || (strcmp(pTxt, "high") == 0)) {
                t = setPriority(t, pTxt);
                break;
            } else {
                printf("\n!! Error: invalid input, please try again !!");
                memset(pTxt, '\0', sizeof(pTxt));
            }
        }
        
        while (!isValidDate(newDeadline)) {
            printf("\nEnter the new deadline (format ddmmyyyy): ");
            read(8, newDeadline);
            if (!isValidDate(newDeadline)) {
                printf("\n!! Invalid date !! Please try again !!");
            }
        }
        t = setDeadline(t, newDeadline);
        if (t == NULL) {
            printf("\nError: invalid deadline.\n");
            return 1;
        }

        enqueue(p->inProgress, popL(&(p->expired), t));
        printf("\nTask '%s' successfully restored.\n", title);
    } else {
        printf("\nTask with title '%s' not found in the expired list.\n", title);
    }

    return 0;
}

void printPlanner(Planner p) {
    if (p == NULL) {
        printf("\nPlanner not initialized.\n");
        return;
    }

    clearScreen();
    printf("\n\n\t      --- Planner ---\n\n");
    printList(p->completed);
    printQueue(p->inProgress);
    printList(p->expired);
    printf("\n\nPress x to continue...\n");
    while (getchar() != 'x');
}

int insert(Planner p) {
    if (p == NULL) {
        printf("\nPlanner not initialized.\n");
        return 0;
    }

    Task t = newTask();
    if (t == NULL) {
        printf("\nError: memory allocation for the task failed.\n");
        return 0;
    }

    if (enqueue(p->inProgress, t)) {
        printf("\n\nTask successfully added to the in-progress queue.\n");
        printf("\n\nPress x to continue...\n");
        while (getchar() != 'x');
        return 1;
    } else {
        printf("\n\nError: task insertion into the in-progress queue failed.\n");
        printf("\n\nPress x to continue...\n");
        while (getchar() != 'x');
        return 0;
    }
}

Planner modifyTask(Planner p) {
    if (p == NULL) {
        printf("\nError: planner does not exist.\n");
        return 0;
    }

    char title[21], ans;
    int choice;
    Task t;
    do {
        clearBuffer();
        printf("\nEnter the title of the task to modify: ");
        read(20, title);
        t = getByPQTitle(p->inProgress, title);
        printf("\nThe selected task is: \n\n");
        printTaskDetails(t);
        printf("\n\nWould you pick another task? (y/n) ");
        scanf("%c", &ans);
    } while (ans != 'n');

    do {
        clearScreen();
        printf("\n\n\t      --- Modification Menu ---\n\n");
        printf("1. Change title\n");
        printf("2. Change description\n");
        printf("3. Change course\n");
        printf("4. Change estimated time\n");
        printf("5. Change deadline\n");
        printf("6. Change priority\n");
        printf("7. Change completion percentage\n");
        printf("8. See the changes made\n");
        printf("0. Return to main menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                clearBuffer(); 
                printf("\nEnter the new title (max 20): ");
                read(20, title);
                setTitle(t, title);
                printf("\nTitle successfully changed to '%s'.\n", title);
                break;
            }
            case 2: {
                clearBuffer(); 
                char newDescription[256];
                printf("\nEnter the new description (max 255): ");
                read(256, newDescription);
                setDescription(t, newDescription);
                printf("\nDescription successfully changed for task '%s'.\n", title);
                break;
            }
            case 3: {
                clearBuffer(); 
                char newCourse[50];
                printf("\nEnter the new course (max 50): ");
                read(50, newCourse);
                setCourse(t, newCourse);
                printf("\nCourse successfully changed for task '%s'.\n", title);
                break;
            }
            case 4: {
                clearBuffer();
                int newEstimatedTime;
                do {
                    if (newEstimatedTime < 0) printf("\nError: estimated time cannot be negative.");
                    printf("\nEnter the new estimated time (in minutes): ");
                    scanf("%d", &newEstimatedTime);
                } while (newEstimatedTime < 0);
                setExdTime(t, newEstimatedTime);
                printf("\nEstimated time successfully changed for task '%s'.\n", title);
                break;
            }
            case 5: {
                clearBuffer(); 
                char newDeadline[9];
                while (!isValidDate(newDeadline)) {
                    printf("\nEnter the new deadline (format ddmmyyyy): ");
                    read(8, newDeadline);
                    if (!isValidDate(newDeadline)) {
                        printf("\n!! Invalid date !! Please try again !!");
                    }
                }
                setDeadline(t, newDeadline);
                printf("\nDeadline successfully changed for task '%s'.\n", title);
                break;
            }
            case 6: {
                clearBuffer(); 
                char pTxt[6];
                while (1) {
                    printf("\nEnter priority level (low/medium/high): ");
                    read(6, pTxt);

                    if ((strcmp(pTxt, "low") != 0) && (strcmp(pTxt, "medium") != 0) && (strcmp(pTxt, "high") != 0)) {
                        printf("\n!! Error: Invalid input, please try again !!");
                        memset(pTxt, '\0', sizeof(pTxt));
                    } else break;
                }
                setPriority(t, pTxt);
                printf("\nPriority successfully changed for task '%s'.\n", title);
                break;
            }
            case 7: {
                clearBuffer(); 
                float newPerc;
                do {
                    printf("\nEnter the new completion percentage (0-100): ");
                    scanf("%f", &newPerc);
                    if (newPerc < 0 || newPerc > 100) {
                        printf("\nError: The percentage must be between 0 and 100.\n");
                    }
                } while (newPerc < 0 || newPerc > 100);
            
                if (newPerc == 100.0) {
                    printf("\nGreat job, the task is complete\n");
                    setCompleted(t, p);
                } else {
                    setCompletionPercentage(t, newPerc);
                    printf("\nCompletion percentage successfully changed for task '%s'.\n", title);
                }
                break;
            }
            case 8: {
                printTaskDetails(t);
                printf("\n\nPress x to continue...\n");
                while (getchar() != 'x');
                break;}
            case 0: break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);
}

int showTaskProgress (Planner p){
    if (p == NULL){
        printf("\nError: planner does not exist\n");
        return 0;
    }
    if (emptyPQ(p->inProgress)) {
        printf("\nThere are no tasks in progress at the moment.\n");
        return 0;
    }
    Task t;
    float timePerc = 0.0;
    int totalTime = 0, timeSpent = 0;

    clearScreen();
    printf("\n\n\t      --- Task Progress ---\n\n");
    for (int i = 0; i < getSize(p->inProgress); i++) {
        t = getByIndex(p->inProgress, i);
        totalTime = compareDates(getDeadline(t), getStartDate(t));
        timeSpent = compareDates(today, getStartDate(t));

        if (totalTime < 0) {
            printf("\nError: start and deadline dates are not valid.\n");
            continue;
        }
        if (totalTime == 0) timePerc = 100.0; 
            else timePerc = ((float)timeSpent / totalTime) * 100.0;

        printf("\nTask %d: %s\n- Completion: %.2f%%\n- Time Progress: %.2f%%\n", 
                i + 1, getTitle(t), getCompletionPercentage(t), timePerc);
    }

    printf("\n\nPress x to continue...\n");
    while (getchar() != 'x');
    return 1;
}

/* searchReport
 * Syntax Specification:
 * bool searchReport(const char *startDate);
 *
 * Semantic Specification:
 * Searches for and displays a weekly report block in the report file that starts with a given date.
 *
 * Preconditions:
 * - 'startDate' must be a valid string representing a date in the format "ddmmyyyy".
 *
 * Postconditions:
 * - Prints the matched report block to the screen.
 * - Returns true if a report is found, false otherwise.
 *
 * Side Effects:
 * - Reads from file.
 * - Outputs to the terminal.
 */
bool searchReport(const char *startDate) {
    FILE *file = fopen("./Data/report.txt", "r");
    if (file == NULL) {
        printf("\nError: Unable to open file.\n");
        return false;
    }

    char line[512];
    bool found = false;
    bool insideBlock = false;

    while (fgets(line, sizeof(line), file)) {
        // Rimuove newline
        line[strcspn(line, "\n")] = 0;

        // Cerca una data intermedia
        if (!insideBlock && strcmp(line, startDate) == 0) {
            found = true;
            clearScreen();
            printf("\nReport generated on date: ");
            printDate(line);
            printf("\n");
            insideBlock = true; // Ora iniziamo a cercare il blocco di testo
            continue;
        }

        // Se abbiamo trovato la data, cerchiamo il primo $
        if (insideBlock) {
            if (line[0] == '$') {
                // Se troviamo il primo $, iniziamo a stampare il contenuto
                while (fgets(line, sizeof(line), file)) {
                    line[strcspn(line, "\n")] = 0;
                    if (line[0] == '$') break; // Stop al secondo $
                    printf("%s\n", line);
                }
                break; // Fermiamo la ricerca dopo aver stampato il blocco
            }
        }
    }

    fclose(file);
    return found;
}

int weeklyReport (Planner p){
    if (p == NULL || (p->inProgress == NULL && p->completed == NULL && p->expired == NULL)) {
        printf("\nError: Report not available.\n");
        return 0;
    }

    if (!searchReport(getPreviousMonday())) {
        printf("\nError: Report not available.");
    }

    printf("\n\nPress x to continue...\n");
    while (getchar() != 'x');
    return 1;
}

int deleteHistory(Planner p){
    if (p == NULL){
        printf("\nError: planner does not exist.\n");
        return 0;
    }
    if (freeList(&(p->completed)) == 1 && freeList(&(p->expired)) == 1) return 1;
    return 0;
}

int deleteTask(Planner p){
    if (p == NULL) {
        printf("\nError: planner does not exist.\n");
        return 0;
    }

    char title[21], ans;
    Task t;
    do {
        clearBuffer();
        printf("\nEnter the title of the task to delete: ");
        read(20, title);
        t = getByPQTitle(p->inProgress, title);
        
        printf("\nThe selected task is: \n\n");
        printTaskDetails(t);
        printf("\n\nWould you pick an another task? (y/n) ");
        scanf("%c", &ans);
    } while (ans != 'n');

    t = pop(p->inProgress, t);
    freeTask(t);
}
