#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "../task/task.h"

struct node {
    Task value;
    struct node *next;
};

/* newList
 * Syntax Specification:
 * list newList();
 *
 * Semantic Specification:
 * Initializes an empty list.
 *
 * Preconditions:
 * - None.
 *
 * Postconditions:
 * - Returns NULL representing an empty list.
 *
 * Side Effects:
 * - None.
 */
list newList() {
    return NULL;
}

/* emptyList
 * Syntax Specification:
 * int emptyList(list l);
 *
 * Semantic Specification:
 * Checks if the list is empty.
 *
 * Preconditions:
 * - 'l' must be a valid list.
 *
 * Postconditions:
 * - Returns 1 if empty, 0 otherwise.
 *
 * Side Effects:
 * - None.
 */
int emptyList(list l) {
    return l == NULL;
}

/* getValue
 * Syntax Specification:
 * Task getValue(list l);
 *
 * Semantic Specification:
 * Returns the value of the first node in the list.
 *
 * Preconditions:
 * - 'l' must be non-NULL.
 *
 * Postconditions:
 * - Returns the Task in the first node or NULL on error.
 *
 * Side Effects:
 * - Prints error message if list is NULL.
 */
Task getValue(list l) {
    if (l == NULL) {
        printf("\nError: list is empty or non-existent\n");
        return NULL;
    }
    return l->value;
}

/* getNext
 * Syntax Specification:
 * struct node* getNext(list l);
 *
 * Semantic Specification:
 * Returns the next node in the list.
 *
 * Preconditions:
 * - 'l' must be non-NULL.
 *
 * Postconditions:
 * - Returns the next node pointer.
 *
 * Side Effects:
 * - Prints error message if list is NULL.
 */
struct node *getNext(list l) {
    if (l == NULL) {
        printf("\nError: list is empty or non-existent\n");
        return NULL;
    }
    return l->next;
}

/* consList
 * Syntax Specification:
 * list consList(Task val, list l);
 *
 * Semantic Specification:
 * Prepends a new Task to the list.
 *
 * Preconditions:
 * - 'val' must be a valid Task.
 *
 * Postconditions:
 * - Returns the new head of the list.
 *
 * Side Effects:
 * - Allocates memory.
 */
list consList(Task val, list l) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node != NULL) {
        new_node->value = val;
        new_node->next = l;
        l = new_node;
    } else {
        printf("Memory allocation error\n");
    }
    return l;
}

/* tailList
 * Syntax Specification:
 * list tailList(list l);
 *
 * Semantic Specification:
 * Returns the list excluding its first node.
 *
 * Preconditions:
 * - 'l' must be valid.
 *
 * Postconditions:
 * - Returns the next node or NULL.
 *
 * Side Effects:
 * - None.
 */
list tailList(list l) {
    return (l != NULL) ? l->next : NULL;
}

/* getFirst
 * Syntax Specification:
 * Task getFirst(list l);
 *
 * Semantic Specification:
 * Retrieves the first Task in the list.
 *
 * Preconditions:
 * - 'l' must be valid.
 *
 * Postconditions:
 * - Returns the first Task or NULL.
 *
 * Side Effects:
 * - None.
 */
Task getFirst(list l) {
    return (l != NULL) ? l->value : NULL;
}

/* getByLTitle
 * Syntax Specification:
 * Task getByLTitle(list l, char *title);
 *
 * Semantic Specification:
 * Searches the list for a task by its title.
 *
 * Preconditions:
 * - 'l' and 'title' must be valid.
 *
 * Postconditions:
 * - Returns the matching Task or NULL.
 *
 * Side Effects:
 * - None.
 */
Task getByLTitle(list l, char *title) {
    while (l != NULL) {
        if (strcmp(getTitle(l->value), title) == 0) {
            return l->value;
        }
        l = l->next;
    }
    return NULL;
}

/* printList
 * Syntax Specification:
 * void printList(list l);
 *
 * Semantic Specification:
 * Prints each task in the list with formatting.
 *
 * Preconditions:
 * - 'l' must be valid.
 *
 * Postconditions:
 * - Task info is printed to stdout.
 *
 * Side Effects:
 * - Writes to stdout.
 */
void printList(list l) {
    if (l == NULL) return;

    int i = 1;
    printf("\n\t***************************\n");
    while (l != NULL) {
        if (i == 1) (getCompletionPercentage(l->value) == 100.0) ? printf("\n\t    - completed tasks: -    \n\n") : printf("\n\t    - expired tasks: -    \n\n");
        printf("Task %d ", i++);
        printTask(l->value);
        l = l->next;
    }
    printf("\n\t***************************\n\n");
}

/* rmvList
 * Syntax Specification:
 * list rmvList(list l, char *title);
 *
 * Semantic Specification:
 * Removes the task with the matching title.
 *
 * Preconditions:
 * - 'l' and 'title' must be valid.
 *
 * Postconditions:
 * - Task is removed if found.
 *
 * Side Effects:
 * - Modifies the list, frees memory.
 */
list rmvList(list l, char *title) {
    list now = l, temp = (now != NULL) ? now->next : NULL;

    while (now != NULL && temp != NULL) {
        if (strcmp(getTitle(temp->value), title) == 0) {
            now->next = temp->next;
            free(temp->value);
            free(temp);
            return now;
        }
        now = now->next;
        if (now != NULL) temp = now->next;
    }

    printf("\nElement not found");
    return l;
}

/* popL
 * Syntax Specification:
 * Task popL(list *l, Task target);
 *
 * Semantic Specification:
 * Removes the target task from the list.
 *
 * Preconditions:
 * - 'l' and 'target' must be valid.
 *
 * Postconditions:
 * - Task is removed and returned.
 *
 * Side Effects:
 * - Modifies list, frees node memory.
 */
Task popL(list *l, Task target) {
    if (l == NULL || target == NULL) {
        printf("\nError: list or task is NULL\n");
        return NULL;
    }

    list now = *l, prev = NULL;
    while (now != NULL) {
        if (now->value == target) {
            if (prev == NULL) {
                *l = now->next;
            } else {
                prev->next = now->next;
            }
            Task removed = now->value;
            free(now);
            return removed;
        }
        prev = now;
        now = now->next;
    }
    return NULL;
}

/* saveOnFileList
 * Syntax Specification:
 * int saveOnFileList(list l, char *filename);
 *
 * Semantic Specification:
 * Saves the task list to a file.
 *
 * Preconditions:
 * - 'l' and 'filename' must be valid.
 *
 * Postconditions:
 * - Returns 1 if success, 0 on error.
 *
 * Side Effects:
 * - File I/O operations.
 */
int saveOnFileList(list l, char *filename) {
    if (l == NULL || filename == NULL) {
        printf("\nError: list or filename is NULL\n");
        return 0;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nError opening file\n");
        return 0;
    }

    while (l != NULL) {
        fPrintTask(l->value, file);
        l = l->next;
    }
    fclose(file);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nTemporary file error.\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return (size > 0) ? 1 : (printf("\nFile was not updated correctly\n"), 0);
}

/* scanFileList
 * Syntax Specification:
 * list scanFileList(list l, FILE *f);
 *
 * Semantic Specification:
 * Reads tasks from a file and constructs a list.
 *
 * Preconditions:
 * - 'f' must be a valid file pointer.
 *
 * Postconditions:
 * - Returns the populated list.
 *
 * Side Effects:
 * - File I/O operations, memory allocation.
 */
list scanFileList(list l, FILE *f) {
    if (f == NULL) {
        printf("\nRead from file failed.\n");
        return NULL;
    }

    Task item;
    while (1) {
        item = fReadTask(f);
        if (item == NULL) break;
        l = consList(item, l);
    }
    fclose(f);
    return l;
}

/* freeList
 * Syntax Specification:
 * int freeList(list l);
 *
 * Semantic Specification:
 * Frees all memory associated with the list.
 *
 * Preconditions:
 * - 'l' must be a valid list.
 *
 * Postconditions:
 * - Memory is released.
 *
 * Side Effects:
 * - Frees memory.
 */
int freeList(list *l) {
    if (l == NULL) return 0;

    while (*l != NULL) {
        if (!freeTask(popL(l, getValue(*l)))) return 0;
    }

    free(*l);
    return 1;
}
