#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pQueue.h"
#include "../task/task.h"

struct PQ {
    int tot;
    Task *arr;
    int numel;
};

/* newPQ
 * Syntax Specification:
 * pQueue newPQ();
 *
 * Semantic Specification:
 * Allocates and initializes a new priority queue.
 *
 * Preconditions:
 * - None.
 *
 * Postconditions:
 * - Returns a pointer to a valid priority queue.
 *
 * Side Effects:
 * - Allocates memory.
 */
pQueue newPQ() {
    pQueue q = malloc(sizeof(struct PQ));
    if (q == NULL) return NULL;
    q->numel = 0;
    q->tot = 8;
    q->arr = malloc(sizeof(Task) * 8);
    for (int i = 0; i < 8; i++)
        q->arr[i] = NULL;
    return q;
}

/* emptyPQ
 * Syntax Specification:
 * int emptyPQ(pQueue q);
 *
 * Semantic Specification:
 * Checks if the priority queue is empty.
 *
 * Preconditions:
 * - 'q' must be a valid pointer or NULL.
 *
 * Postconditions:
 * - Returns 1 if empty, 0 otherwise.
 *
 * Side Effects:
 * - None.
 */
int emptyPQ(pQueue q) {
    if (!q) return 1;
    return q->numel == 0;
}

/* getSize
 * Syntax Specification:
 * int getSize(pQueue q);
 *
 * Semantic Specification:
 * Returns the number of elements in the priority queue.
 *
 * Preconditions:
 * - 'q' must be a valid pointer to a priority queue.
 *
 * Postconditions:
 * - Returns the number of elements or -1 if 'q' is NULL.
 *
 * Side Effects:
 * - Prints error message if 'q' is NULL.
 */
int getSize(pQueue q) {
    if (q == NULL) {
        printf("\nError: queue is null or empty\n");
        return -1;
    }
    return q->numel;
}

/* getByIndex
 * Syntax Specification:
 * Task getByIndex(pQueue q, int index);
 *
 * Semantic Specification:
 * Retrieves the Task at the specified index from the queue.
 *
 * Preconditions:
 * - 'q' must be a valid priority queue.
 * - 'index' must be within bounds.
 *
 * Postconditions:
 * - Returns the Task at the given index or NULL on error.
 *
 * Side Effects:
 * - Prints error message if 'q' is NULL or index is invalid.
 */

Task getByIndex(pQueue q, int index) {
    if (q == NULL || index < 0 || index >= q->numel) {
        printf("\nError: queue is null or index out of bounds\n");
        return NULL;
    }
    return q->arr[index];
}

/* getMax
 * Syntax Specification:
 * Task getMax(pQueue q);
 *
 * Semantic Specification:
 * Retrieves the Task with the highest priority.
 *
 * Preconditions:
 * - 'q' must be a valid non-empty priority queue.
 *
 * Postconditions:
 * - Returns the Task with the highest priority.
 *
 * Side Effects:
 * - None.
 */
Task getMax(pQueue q) {
    return q->arr[0];
}


int deleteMax(pQueue q) {
    if (!q || q->numel == 0) return 0;

    q->arr[0] = q->arr[q->numel - 1];
    q->numel--;
    scendi(q, 0);
    return 1;
}

/* scendi
 * Syntax Specification:
 * static void scendi(pQueue q, int pos);
 *
 * Semantic Specification:
 * Restores the heap property from a given index downwards.
 *
 * Preconditions:
 * - 'q' must be a valid heap.
 * - 'pos' must be a valid index within the heap.
 *
 * Postconditions:
 * - Heap property is restored from position 'pos'.
 *
 * Side Effects:
 * - Modifies the internal array.
 */

static void scendi(pQueue q, int pos) {
    int left, right, max;
    int n = q->numel;

    while (1) {
        left = 2 * pos + 1;
        right = 2 * pos + 2;
        max = pos;

        if (left < n && getPriority(q->arr[left]) > getPriority(q->arr[max])) {
            max = left;
        }

        if (right < n && getPriority(q->arr[right]) > getPriority(q->arr[max])) {
            max = right;
        }

        if (max == pos) {
            break;
        }

        Task temp = q->arr[pos];
        q->arr[pos] = q->arr[max];
        q->arr[max] = temp;

        pos = max;
    }
}

/* enqueue
 * Syntax Specification:
 * int enqueue(pQueue q, Task key);
 *
 * Semantic Specification:
 * Adds a new Task to the priority queue and maintains heap order.
 *
 * Preconditions:
 * - 'q' must be a valid priority queue.
 * - 'key' must be a valid Task.
 *
 * Postconditions:
 * - The new Task is added and the heap is adjusted.
 * - Queue may be reallocated to accommodate more elements.
 *
 * Side Effects:
 * - Modifies the queue, may allocate new memory.
 */
int enqueue(pQueue q, Task key) {
    if (q->numel == q->tot) {
        q->tot += 8;
        Task *temp = realloc(q->arr, q->tot * sizeof(Task));
        if (!temp) {
            fprintf(stderr, "Realloc error\n");
            return 0;
        }
        q->arr = temp;
    }
    q->arr[q->numel++] = key;
    sali(q);
    return 1;
}

/* sali
 * Syntax Specification:
 * static void sali(pQueue q);
 *
 * Semantic Specification:
 * Restores the heap property upwards from the last inserted element.
 *
 * Preconditions:
 * - 'q' must be a valid heap.
 *
 * Postconditions:
 * - Heap property is restored.
 *
 * Side Effects:
 * - Modifies the internal array.
 */
static void sali(pQueue q) {
    int pos = q->numel - 1;
    int parent = (pos - 1) / 2;

    while (pos > 0 && getPriority(q->arr[pos]) > getPriority(q->arr[parent])) {
        Task temp = q->arr[pos];
        q->arr[pos] = q->arr[parent];
        q->arr[parent] = temp;

        pos = parent;
        parent = (pos - 1) / 2;
    }
}
/* freePQ
 * Syntax Specification:
 * void freePQ(pQueue q);
 *
 * Semantic Specification:
 * Deallocates all memory associated with the given priority queue, including its internal array and each task it contains.
 *
 * Preconditions:
 * - q can be NULL or a valid pointer to a priority queue structure.
 *
 * Postconditions:
 * - All dynamically allocated memory related to the queue is freed.
 *
 * Side Effects:
 * - Frees memory using free().
 */
void freePQ(pQueue q) {
    if (q == NULL) return;

    for (int i = 0; i < q->numel; i++) {
        free(q->arr[i]);
    }

    free(q->arr);
    free(q);
}

/* printQueue
 * Syntax Specification:
 * void printQueue(pQueue q);
 *
 * Semantic Specification:
 * Prints the list of tasks currently in the priority queue to the standard output.
 *
 * Preconditions:
 * - q must be a valid (non-NULL) priority queue.
 *
 * Postconditions:
 * - The list of tasks is printed to the terminal, if any are present.
 *
 * Side Effects:
 * - Uses printf to output task data.
 */
void printQueue(pQueue q) {
    if (q == NULL || q->numel == 0) {
        return;
    }

    printf("\n\t***************************\n");
    printf("\n\t   - Tasks in progress: -    \n\n");
    for (int i = 0; i < q->numel; i++) {
        printf("Task %d ", i + 1);
        printTask(q->arr[i]);
    }
    printf("\n\t***************************\n\n");
}

/* scanFileQueue
 * Syntax Specification:
 * pQueue scanFileQueue(pQueue q, FILE *f);
 *
 * Semantic Specification:
 * Reads tasks from the specified file and inserts them into the given priority queue.
 *
 * Preconditions:
 * - f must point to a readable file.
 * - q must be a valid, initialized priority queue.
 *
 * Postconditions:
 * - The queue q is populated with tasks read from the file.
 * - The file is closed after reading.
 *
 * Side Effects:
 * - Reads from a file.
 * - Enqueues tasks.
 * - Closes the file.
 */
pQueue scanFileQueue(pQueue q, FILE *f) {
    if (f == NULL) {
        printf("\nFile read failed.\n");
        return NULL;
    }

    Task item;
    while (1) {
        item = fReadTask(f);
        if (item == NULL) break;
        enqueue(q, item);
    }

    fclose(f);
    return q;
}

/* getByPQTitle
 * Syntax Specification:
 * Task getByPQTitle(pQueue q, char *title);
 *
 * Semantic Specification:
 * Searches for a task with the given title in the priority queue and returns it if found.
 *
 * Preconditions:
 * - q must be a valid priority queue.
 * - title must be a non-NULL string.
 *
 * Postconditions:
 * - Returns a pointer to the task with the given title, or NULL if not found.
 *
 * Side Effects:
 * - None.
 */
Task getByPQTitle(pQueue q, char *title) {
    for (int i = 0; i < q->numel; i++) {
        if (strcmp(getTitle(q->arr[i]), title) == 0) {
            return q->arr[i];
        }
    }
    return NULL;
}

/* saveOnFileQueue
 * Syntax Specification:
 * int saveOnFileQueue(pQueue q, char *filename);
 *
 * Semantic Specification:
 * Writes the contents of the priority queue to a file. Returns 1 if successful, 0 otherwise.
 *
 * Preconditions:
 * - q and filename must not be NULL.
 *
 * Postconditions:
 * - A file is created or overwritten with the queue data.
 * - Returns 1 if the file was successfully written and verified; otherwise 0.
 *
 * Side Effects:
 * - Writes to a file.
 * - Opens and closes files.
 */
int saveOnFileQueue(pQueue q, char *filename) {
    if (q == NULL || filename == NULL) {
        printf("\nError: queue or filename is NULL\n");
        return 0;
    }

    FILE *temp = fopen(filename, "w");
    if (temp == NULL) {
        printf("\nFile open error\n");
        return 0;
    }

    for (int i = 0; i < q->numel; i++) {
        fPrintTask(q->arr[i], temp);
    }
    fclose(temp);

    FILE *check = fopen(filename, "r");
    if (check == NULL) {
        printf("\nTemporary file error.\n");
        return 0;
    }

    fseek(check, 0, SEEK_END);
    long size = ftell(check);
    fclose(check);

    return (size > 0) ? 1 : (printf("\nFile was not updated\n"), 0);
}

/* getIndexByTask
 * Syntax Specification:
 * int getIndexByTask(pQueue q, Task t);
 *
 * Semantic Specification:
 * Returns the index of the given task in the priority queue, or -1 if the task is not found.
 *
 * Preconditions:
 * - q and t must not be NULL.
 *
 * Postconditions:
 * - Returns the task's index if found, otherwise -1.
 *
 * Side Effects:
 * - None.
 */
int getIndexByTask(pQueue q, Task t) {
    if (q == NULL || t == NULL) {
        printf("\nError: queue or task is NULL\n");
        return -1;
    }

    for (int i = 0; i < q->numel; i++) {
        if (q->arr[i] == t) {
            return i;
        }
    }
    return -1;
}

/* deleteByIndex
 * Syntax Specification:
 * int deleteByIndex(pQueue q, int index);
 *
 * Semantic Specification:
 * Deletes the task at the specified index from the priority queue and reorders the heap.
 *
 * Preconditions:
 * - q must not be NULL.
 * - index must be within bounds of the queue.
 *
 * Postconditions:
 * - Task at the given index is removed.
 * - Queue is reordered to maintain priority.
 * - Returns 1 if deletion is successful, 0 otherwise.
 *
 * Side Effects:
 * - Modifies the queue's contents.
 * - Frees memory of the deleted task.
 */
int deleteByIndex(pQueue q, int index) {
    if (q == NULL || index < 0 || index >= q->numel) {
        printf("\nError: queue is NULL or index out of bounds\n");
        return 0;
    }

    free(q->arr[index]);
    q->arr[index] = q->arr[q->numel - 1];
    q->numel--;
    scendi(q, index);
    return 1;
}

/* pop
 * Syntax Specification:
 * Task pop(pQueue q, Task target);
 *
 * Semantic Specification:
 * Removes a specific task from the priority queue and returns it. Reorders the queue accordingly.
 *
 * Preconditions:
 * - q and target must not be NULL.
 * - target must exist in the queue.
 *
 * Postconditions:
 * - The task is removed from the queue and returned.
 * - The queue is re-ordered to maintain priority.
 *
 * Side Effects:
 * - Modifies the queue.
 */
Task pop(pQueue q, Task target) {
    if (q == NULL || target == NULL) {
        printf("Error: queue or task is NULL\n");
        return NULL;
    }

    int index = getIndexByTask(q, target);
    if (index == -1) {
        printf("Error: task not found in queue\n");
        return NULL;
    }

    Task taskToReturn = q->arr[index];
    q->arr[index] = q->arr[q->numel - 1];
    q->numel--;
    scendi(q, index);

    return taskToReturn;
}

