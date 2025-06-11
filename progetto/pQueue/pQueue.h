#include "../task/task.h"

typedef struct PQ *pQueue;

 //priority queue prototypes 
pQueue newPQ();
int emptyPQ(pQueue);
void freePQ(pQueue);

Task getMax(pQueue); 
int deleteMax(pQueue);

static void scendi(pQueue, int);
static void sali(pQueue);

int enqueue(pQueue, Task);

void printQueue(pQueue);
pQueue scanFileQueue(pQueue, FILE *);
int saveOnFileQueue(pQueue, char *);

int getSize(pQueue);
Task getByIndex(pQueue, int);
Task getByPQTitle(pQueue, char *);
int getIndexByTask(pQueue, Task);
Task pop(pQueue, Task);
int deleteByIndex(pQueue q, int index);