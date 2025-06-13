// inclusion of functions for managing input/output and dates
#include "../char/char.h"

// Forward declaration of the planner struct
typedef struct planner *Planner;
#ifndef DEFAULT_TXT_FOLDER
#define DEFAULT_TXT_FOLDER "Data"
#endif

//planner prototypes
Planner openPlanner(void);
int closePlanner(Planner p);   
int restoreExpiredTask(Planner p); 
Planner modifyTask(Planner p);
void printPlanner(Planner p);
int insert(Planner p);
int weeklyReport (Planner p);
int showTaskProgress (Planner p);
int deleteHistory(Planner p);
int deleteTask(Planner p);

