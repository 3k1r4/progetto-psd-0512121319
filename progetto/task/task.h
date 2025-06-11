#include "../char/char.h"

// Forward declaration of the task struct
typedef struct task *Task;

 //tisk prototypes
Task newTask();

char *getTitle(Task t);
Task setTitle(Task t, const char *title);

char *getDescription(Task t);
Task setDescription(Task t, const char *description);

char *getCourse(Task t);
Task setCourse(Task t, const char *course);

int getExdTime(Task t);
Task setExdTime(Task t, int time);

int getPriority(Task t);
Task setPriority(Task t, char *pTxt);

float getCompletionPercentage(Task t);
Task setCompletionPercentage(Task t, float perc);

char *getCompletionDate(Task t);
Task setCompletionDate(Task t, const char *date);

char *getDeadline(Task t);
Task setDeadline(Task t, const char *date);

char *getStartDate(Task t);
Task setStartDate(Task t);

Task fReadTask(FILE *f);
void printTaskDetails(Task t);
void printTask(Task t);
void fPrintTask(Task t, FILE *f);

int freeTask(Task t);
