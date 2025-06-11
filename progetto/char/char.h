
#include <stdbool.h>
extern char *today; // "ddmmyyyy\0"

void clearScreen();
void clearBuffer();

int read(int, char*);
bool isOnlyDigits(const char *, int); 

bool isValidDate(const char *);
int compareDates(const char *, const char *);
void printDate(const char *);
void fprintDate(FILE *reportFile, const char *date);
char *getCurrentDateAT();
char *getCurrentDateML();
char* getPreviousMonday();
char *intToString(int);
char* getLastWeekDate();

