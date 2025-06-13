#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./planner/planner.h"

int insertTest();
int modifyTest();
int progressTest();
int reportTest();

int main(void){

     // Reindirizza l'input da insert.txt
    //if (freopen("./test/input/insert.txt", "r", stdin) == NULL) {
    //    perror("Errore nell'apertura di insert.txt");
    //    exit(EXIT_FAILURE);
    //}

    //if (!insertTest()) printf("Insert error.");
    //if (!modifyTest()) printf("\nModify error.");
    //if (!progressTest()) printf("\nShow progress error.");
    //if (!reportTest()) printf("\nWeekly report error.");

    return 0;
}

int insertTest(){
    freopen("./test/input/insert.txt", "r", stdin);
    Planner planner;

    for (int i = 0; i < 4; i ++){
        clearBuffer();
        today = getCurrentDateML();
        if (strcmp(today, "01062025") == 0) if ((planner = openPlanner()) == NULL) return 0;
        if (strcmp(today, "09062025") == 0) if (!insert(planner)) return 0;
        if (!insert(planner)) return 0;
    }

    closePlanner(planner);
    return 1;
}

int modifyTest(){
    freopen("./test/input/modify.txt", "r", stdin);
    today = getCurrentDateML();
    Planner planner;
    if ((planner = openPlanner()) == NULL) return 0;

    for (int i = 0; i < 3; i++) if (!modifyTask(planner)) return 0;

    closePlanner(planner);
    return 1;
}

int progressTest(){
    freopen("./test/input/progress.txt", "r", stdin);
    today = getCurrentDateML();
    Planner planner;
    if ((planner = openPlanner()) == NULL) return 0;

    if (!showTaskProgress(planner)) return 0;
    
    return 1;
}

int reportTest(){
    freopen("./test/input/report.txt", "r", stdin);
    today = getCurrentDateML();
    Planner planner;
    if ((planner = openPlanner()) == NULL) return 0;

    if (!weeklyReport(planner)) return 0;

    closePlanner(planner);
    return 1;
}