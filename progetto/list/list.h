#include "../task/task.h"

typedef struct node *list;

 //List prototypes 
 list newList();
 int emptyList(list l);
 int freeList(list *);

 list consList(Task val, list l);
 Task getFirst (list l);
 Task getValue(list l);
 struct node *getNext(list l);
 Task getByLTitle(list l, char *c);

 list tailList(list l);
 Task popL (list *l, Task target);
 list rmvList( list l, char *c);
 
 void printList(list);
 int saveOnFileList(list l, const char *c);
 list scanFileList(list l, FILE *f);
 
 
