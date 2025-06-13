#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./planner/planner.h"

int insertTest();
int modifyTest();
int reportTest();

bool compare_files(const char *file1, const char *file2);

int main(void){

    if (!insertTest() || 
        !compare_files("./test/oracle/progress.txt", "./test/output/progress.txt")) {
            printf("\nInsert error.");
            return 1;
        }

    if (!modifyTest() || 
        !compare_files("./test/oracle/progress.txt", "./test/output/progress.txt") ||
        !compare_files("./test/oracle/completed.txt", "./test/output/completed.txt") ||     
        !compare_files("./test/oracle/expired.txt", "./test/output/expired.txt")) {
            printf("\nModify error.");
            return 1;
        }
    
    if (!reportTest() ||
        !compare_files("./test/oracle/report.txt", "./test/output/report.txt")) {
            printf("\nWeekly report error.");
            return 1;
        }

    printf("\nAll the tests gone well.");
    return 0;
}

int insertTest(){
    //freopen("./test/input/insert.txt", "r", stdin);
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
    //freopen("./test/input/modify.txt", "r", stdin);
    today = getCurrentDateML();
    Planner planner;
    if ((planner = openPlanner()) == NULL) return 0;

    for (int i = 0; i < 3; i++) if (!modifyTask(planner)) return 0;

    closePlanner(planner);
    return 1;
}

int reportTest(){
    //freopen("./test/input/report.txt", "r", stdin);
    today = getCurrentDateML();
    Planner planner;
    if ((planner = openPlanner()) == NULL) return 0;

    if (!weeklyReport(planner)) return 0;

    closePlanner(planner);
    return 1;
}

#include <stdio.h>
#include <stdbool.h>

bool compare_files(const char *file1, const char *file2) {
    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        return false;
    }

    int ch1, ch2;
    while ((ch1 = fgetc(fp1)) != EOF && (ch2 = fgetc(fp2)) != EOF) {
        if (ch1 != ch2) {
            fclose(fp1);
            fclose(fp2);
            return false;
        }
    }

    // Controlla se entrambi i file hanno raggiunto EOF
    bool result = (ch1 == EOF && ch2 == EOF);

    fclose(fp1);
    fclose(fp2);
    return result;
}