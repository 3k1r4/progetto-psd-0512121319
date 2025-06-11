#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "task.h"
#include "../char/char.h"

// Definition of the task structure
struct task {
    char title[21];
    char description[256];
    char course[51];
    int estimatedTime;
    char startDate[9];
    char deadline[9];
    int priority;
    float completionPercentage;
    char completionDate[9];
};

/* newTask
 * Syntax Specification:
 * Task newTask();
 *
 * Semantic Specification:
 * Allocates and initializes a new task by requesting user input for all the required fields.
 * Initializes completion percentage to 0 and assigns today's date as the start date.
 *
 * Preconditions:
 * - 'today' must be a valid date string defined externally.
 * - Functions clearBuffer(), read(), and isValidDate() must be available.
 *
 * Postconditions:
 * - Returns a pointer to a fully initialized Task.
 *
 * Side Effects:
 * - Reads user input from terminal.
 * - Prints prompts to terminal.
 * - Allocates memory dynamically.
 */
Task newTask() {
    char pTxt[6];
    Task new = malloc(sizeof(struct task));

    clearBuffer();
    printf("\nEnter title (max 20): ");
    read(20, new->title);
    printf("\nEnter description (max 255): ");
    read(255, new->description);
    printf("\nEnter course name (max 50): ");
    read(50, new->course);
    

    do {
        printf("\nEnter estimated time (in minutes): ");
        scanf("%d", &new->estimatedTime);
        if (new->estimatedTime < 0) printf("\nError: estimated time cannot be negative.");
    } while (new->estimatedTime < 0);

    while (!isValidDate(new->deadline)) {
        clearBuffer();
        printf("\nEnter deadline (format ddmmyyyy): ");
        read(8, new->deadline);
        if (!isValidDate(new->deadline)) {
            printf("\n!! Invalid date !! Try again !!");
        }
    }

    while (1) {
        printf("\nEnter priority level (low/medium/high): ");
        read(6, pTxt);

        if ((strcmp(pTxt, "low") == 0) || (strcmp(pTxt, "medium") == 0) || (strcmp(pTxt, "high") == 0)) {
            new = setPriority(new, pTxt);
            break;
        } else {
            printf("\n!! Error, try again !!");
            memset(pTxt, '\0', sizeof(pTxt));
        }
    }

    new->completionPercentage = 0.0;
    strcpy(new->startDate, today);
    strcpy(new->completionDate, "00000000"); // Placeholder for uncompleted task

    clearScreen();
    printf("\nNew data added:\n");
    printTaskDetails(new);
    return new;
}

/* getTitle
 * Syntax Specification:
 * char* getTitle(Task t);
 *
 * Semantic Specification:
 * Returns the title of the given task.
 *
 * Preconditions:
 * - 't' must not be NULL.
 *
 * Postconditions:
 * - Returns a pointer to the title string.
 *
 * Side Effects:
 * - None.
 */
char *getTitle(Task t) {
    return t->title;
}

/* setTitle
 * Syntax Specification:
 * Task setTitle(Task t, const char *title);
 *
 * Semantic Specification:
 * Sets the title of the given task.
 *
 * Preconditions:
 * - 't' must not be NULL.
 * - 'title' must be a valid string.
 *
 * Postconditions:
 * - The task's title is updated.
 *
 * Side Effects:
 * - Prints an error if task is NULL.
 */
Task setTitle(Task t, const char *title) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    strcpy(t->title, title);
    return t;
}

/* getDescription, setDescription, getCourse, setCourse, getEstimatedTime, setEstimatedTime, etc.
 * they have similar specifications, so they will be skipped
 */
char *getDescription(Task t) {
    return t->description;
}

Task setDescription(Task t, const char *description) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    strcpy(t->description, description);
    return t;
}

char *getCourse(Task t) {
    return t->course;
}

Task setCourse(Task t, const char *course) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    strcpy(t->course, course);
    return t;
}

int getExdTime(Task t) {
    return t->estimatedTime;
}

Task setExdTime(Task t, int time) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    t->estimatedTime = time;
    return t;
}

int getPriority(Task t) {
    return t->priority;
}

Task setPriority(Task t, char *pTxt) {
    if (t == NULL || pTxt == NULL) {
        printf("\nError: task and/or priority text is NULL\n");
        return NULL;
    }

    if (strcmp(pTxt, "low") == 0) t->priority = 1;
    else if (strcmp(pTxt, "medium") == 0) t->priority = 2;
    else if (strcmp(pTxt, "high") == 0) t->priority = 3;
    else t->priority = 0;

    return t;
}

float getCompletionPercentage(Task t) {
    return t->completionPercentage;
}

Task setCompletionPercentage(Task t, float perc) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    if (perc < 0.0 || perc > 100.0) {
        printf("\nError: invalid percentage. Must be between 0 and 100.\n");
        return NULL;
    }
    t->completionPercentage = perc;
    return t;
}

char *getCompletionDate(Task t) {
    return t->completionDate;
}

Task setCompletionDate(Task t, const char *date) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    if (!isValidDate(date)) {
        printf("\nError: invalid date.\n");
        return NULL;
    }
    strcpy(t->completionDate, date);
    return t;
}

char *getDeadline(Task t) {
    return t->deadline;
}

Task setDeadline(Task t, const char *date) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    if (!isValidDate(date)) {
        printf("\nError: invalid date.\n");
        return NULL;
    }
    strcpy(t->deadline, date);
    return t;
}

char *getStartDate(Task t) {
    return t->startDate;
}

Task setStartDate(Task t) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return NULL;
    }
    strcpy(t->startDate, today);
    return t;
}

/* freadTask
 * Syntax Specification:
 * Task readTaskFromFile(FILE *f);
 *
 * Semantic Specification:
 * Reads a task from a tab-separated text file. If the file content is invalid,
 * returns NULL.
 *
 * Preconditions:
 * - 'f' must be a valid open FILE pointer.
 *
 * Postconditions:
 * - Returns a new Task object with data read from the file, or NULL on failure.
 *
 * Side Effects:
 * - Allocates dynamic memory.
 * - May fail silently if data format is invalid.
 */
Task fReadTask(FILE *f) {
    Task t = malloc(sizeof(struct task));

    int res = fscanf(f, "%20[^\t]\t%255[^\t]\t%50[^\t]\t%d\t%8s\t%8s\t%f\t%8s\t%d\n",
        t->title, t->description, t->course, &t->estimatedTime, t->startDate,
        t->deadline, &t->completionPercentage, t->completionDate, &t->priority);

    if (res != 9) {
        free(t);
        return NULL;
    }
    return t;
}

/* printTaskDetails
 * Syntax Specification:
 * void printTaskDetails(Task t);
 *
 * Semantic Specification:
 * Prints detailed information about a task, including dates and completion status.
 *
 * Preconditions:
 * - 't' must be a valid Task.
 *
 * Postconditions:
 * - Outputs all task information to the terminal.
 *
 * Side Effects:
 * - Interacts with the terminal through print statemnts.
 */
void printTaskDetails(Task t) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return;
    }

    printf("\n\tTitle: %s", t->title);
    printf("\n\tDescription: %s", t->description);
    printf("\n\tCourse: %s", t->course);
    printf("\n\tEstimated Time: %d minutes", t->estimatedTime);
    printf("\n\tStart Date: ");
    printDate(t->startDate);
    printf("\n\tDeadline: ");
    printDate(t->deadline);
    printf("\n\tCompletion Date: ");
    if (strcmp(t->completionDate, "00000000") == 0) {
        printf("Not completed");
    } else {
        printDate(t->completionDate);
    }
    printf("\n\tCompletion Percentage: %.2f%%", t->completionPercentage);
    printf("\n\tPriority: ");
    switch (t->priority) {
        case 1: printf("Low"); break;
        case 2: printf("Medium"); break;
        case 3: printf("High"); break;
        default: printf("Undefined");
    }
}

/* printTask
 * Syntax Specification:
 * void printTask(Task t);
 *
 * Semantic Specification:
 * Displays a compact summary of the task, indicating its current status
 * (completed, expired, due today, or ongoing).
 *
 * Preconditions:
 * - 't' must be a valid Task.
 * - 'today' must be defined externally.
 *
 * Postconditions:
 * - Task status is printed to the terminal.
 *
 * Side Effects:
 * - Calls compareDates and printDate.
 * - Interacts with the terminal through print statements.
 */
void printTask(Task t) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return;
    }

    if (t->completionPercentage == 100.0) {
        printf("- %s (%s) Completed on: ", t->title, t->course);
        printDate(t->completionDate);
        printf("\n");
        return;
    }

    if (compareDates(t->deadline, today) < 0) {
        printf("- %s (%s) Expired on: ", t->title, t->course);
        printDate(t->deadline);
        printf("\n");
        return;
    }

    if (compareDates(t->deadline, today) == 0) {
        printf("- %s (%s) ! Due today !\n", t->title, t->course);
        return;
    }

    printf("- %s (%s) Deadline: ", t->title, t->course);
    printDate(t->deadline);
    printf("\n");
}

/* printTaskToFile
 * Syntax Specification:
 * void printTaskToFile(Task t, FILE *f);
 *
 * Semantic Specification:
 * Writes the task information as a tab-separated line in a file.
 *
 * Preconditions:
 * - 't' must be a valid Task.
 * - 'f' must be a valid writable FILE pointer.
 *
 * Postconditions:
 * - One line of task data is written to the file.
 *
 * Side Effects:
 * - Writes into a file.
 */
void fPrintTask(Task t, FILE *f) {
    if (t == NULL || f == NULL) {
        printf("\nError: task and/or file is NULL or does not exist\n");
        return;
    }

    fprintf(f, "%s\t%s\t%s\t%d\t%s\t%s\t%.2f\t%s\t%d\n",
        t->title, t->description, t->course, t->estimatedTime, t->startDate,
        t->deadline, t->completionPercentage, t->completionDate, t->priority);
}

/* freeTask
 * Syntax Specification:
 * void freeTask(Task t);
 *
 * Semantic Specification:
 * Frees the memory associated with a dynamically allocated Task.
 *
 * Preconditions:
 * - 't' must be a pointer to memory allocated via malloc.
 *
 * Postconditions:
 * - Memory is deallocated.
 *
 * Side Effects:
 * - Frees heap memory.
 * - Prints error if the task is NULL.
 */
int freeTask(Task t) {
    if (t == NULL) {
        printf("\nError: task is NULL or does not exist\n");
        return 0;
    }
    free(t);
}
