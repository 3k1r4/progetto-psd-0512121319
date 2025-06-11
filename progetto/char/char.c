#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "char.h"

char *today = NULL; // Initialized to NULL, will be set in main

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
#endif

/* clearScreen
 * Syntax Specification:
 * void clearScreen();
 *
 * Semantic Specification:
 * Clears the terminal screen.
 *
 * Preconditions:
 * - None.
 *
 * Postconditions:
 * - The terminal screen is cleared.
 *
 * Side Effects:
 * - Calls system command to clear the terminal.
 */
void clearScreen() {
    system(CLEAR_SCREEN);
}

/* clearBuffer
 * Syntax Specification:
 * void clearBuffer();
 *
 * Semantic Specification:
 * Clears the input buffer to avoid leftover characters.
 *
 * Preconditions:
 * - None.
 *
 * Postconditions:
 * - The input buffer is cleared.
 *
 * Side Effects:
 * - Modifies stdin file position.
 */
void clearBuffer(){
    fseek(stdin,0,SEEK_END);
}

/* read
 * Syntax Specification:
 * int read(int max, char *var);
 *
 * Semantic Specification:
 * Reads input from keyboard up to 'max' characters and stores it in 'var'.
 *
 * Preconditions:
 * - 'var' must be a valid pointer with at least 'max + 1' space.
 *
 * Postconditions:
 * - 'var' contains the user input as a null-terminated string.
 *
 * Side Effects:
 * - Reads characters from stdin.
 */
int read(int max, char *var){
    char c;
    int i = 0;
    while (i < max){
        c = getchar();
        if (c == '\n') break;
        var[i++] = c;
    }

    clearBuffer();
    var[i] = '\0';
    return i;
}

/* intToString
 * Syntax Specification:
 * char* intToString(int num);
 *
 * Semantic Specification:
 * Converts an integer into a string representation.
 *
 * Preconditions:
 * - 'num' must be an integer value.
 *
 * Postconditions:
 * - Returns a pointer to a static character array containing the string version of 'num'.
 *
 * Side Effects:
 * - Modifies a static buffer which may be overwritten by future calls.
 */
char *intToString(int num){
    static char string[10];
    sprintf(string, "%d", num); 
    return string;
}

/* isOnlyDigits
 * Syntax Specification:
 * bool isOnlyDigits(const char *s, int len);
 *
 * Semantic Specification:
 * Checks whether a string consists only of digits.
 *
 * Preconditions:
 * - 's' must be a valid pointer to a null-terminated string.
 * - 'len' must not exceed the actual length of 's'.
 *
 * Postconditions:
 * - Returns true if the first 'len' characters are all digits.
 *
 * Side Effects:
 * - None.
 */
bool isOnlyDigits(const char *s, int len) {
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i]))
            return false;
    }
    return true;
}

/* daysInMonth
 * Syntax Specification:
 * int daysInMonth(int month, int year);
 *
 * Semantic Specification:
 * Returns the number of days in the given month and year.
 *
 * Preconditions:
 * - 1 <= month <= 12
 * - year >= 0
 *
 * Postconditions:
 * - Returns 28-31 depending on month and leap year.
 *
 * Side Effects:
 * - None.
 */
int daysInMonth(int month, int year) {
    int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29;
    }
    return daysPerMonth[month - 1];
}

/* isValidDate
 * Syntax Specification:
 * bool isValidDate(const char *date);
 *
 * Semantic Specification:
 * Verifies whether a given date string is valid and not earlier than today.
 *
 * Preconditions:
 * - 'date' must be a null-terminated string in "ddmmyyyy" format.
 *
 * Postconditions:
 * - Returns true if the date is valid and >= today.
 *
 * Side Effects:
 * - None.
 */
bool isValidDate(const char *date) {
    if (strlen(date) != 8 || !isOnlyDigits(date, 8)) {
        return false;
    }

    int day, month, year;
    if (sscanf(date, "%2d%2d%4d", &day, &month, &year) != 3) {
        return false;
    }

    if (month < 1 || month > 12 || day < 1) {
        return false;
    }

    int maxDays = daysInMonth(month, year);
    if (day > maxDays) {
        return false;
    }

    if (today != NULL) {
        int todayDay, todayMonth, todayYear;
        if (sscanf(today, "%2d%2d%4d", &todayDay, &todayMonth, &todayYear) != 3) {
            return false;
        }

        if (year < todayYear ||
            (year == todayYear && month < todayMonth) ||
            (year == todayYear && month == todayMonth && day < todayDay)) {
            return false;
        }
    }
    return true;
}

/* printDate
 * Syntax Specification:
 * void printDate(const char *date);
 *
 * Semantic Specification:
 * Prints the date in "dd/mm/yyyy" format.
 *
 * Preconditions:
 * - 'date' must be a string of exactly 8 digits.
 *
 * Postconditions:
 * - The formatted date is printed to stdout.
 *
 * Side Effects:
 * - Outputs to stdout.
 */
void printDate(const char *date) {
    printf("%c%c/%c%c/%c%c%c%c", date[0], date[1], date[2], date[3], date[4], date[5], date[6], date[7]);
}

void fprintDate(FILE *reportFile, const char *date){
    fprintf(reportFile, "%c%c/%c%c/%c%c%c%c", date[0], date[1], date[2], date[3], date[4], date[5], date[6], date[7]);

}

/* getPreviousMonday
 * Syntax Specification:
 * char* getPreviousMonday();
 *
 * Semantic Specification:
 * Calculates the date of the most recent Monday before or equal to the current date.
 *
 * Preconditions:
 * - The global variable 'today' must be set to a valid date in the format "ddmmyyyy".
 *
 * Postconditions:
 * - Returns a pointer to a static string containing the date of the previous Monday in "ddmmyyyy" format.
 *
 * Side Effects:
 * - Uses and modifies a static buffer.
 */
char* getPreviousMonday() {
    int day, month, year;
    sscanf(today, "%2d%2d%4d", &day, &month, &year);

    struct tm timeStruct = {0};
    timeStruct.tm_mday = day;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_year = year - 1900;

    mktime(&timeStruct);

    int weekDay = timeStruct.tm_wday;
    int daysToMonday = (weekDay == 0) ? 6 : (weekDay - 1);
    
    timeStruct.tm_mday -= daysToMonday;
    mktime(&timeStruct);

    static char mondayDate[9];
    sprintf(mondayDate, "%02d%02d%04d", timeStruct.tm_mday, timeStruct.tm_mon + 1, timeStruct.tm_year + 1900);
    return mondayDate;
}

/* getCurrentDateAT
 * Syntax Specification:
 * char* getCurrentDateAT();
 *
 * Semantic Specification:
 * Returns the current date in "ddmmyyyy" format.
 *
 * Preconditions:
 * - None.
 *
 * Postconditions:
 * - Returns a heap-allocated string with the current date.
 *
 * Side Effects:
 * - Allocates memory.
 */
char *getCurrentDateAT() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *date = malloc(9 * sizeof(char));
    sprintf(date, "%02d%02d%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return date;
}

/* getCurrentDateML
 * Syntax Specification:
 * char* getCurrentDateML();
 *
 * Semantic Specification:
 * Asks the user to input a date in "ddmmyyyy" format and returns it.
 *
 * Preconditions:
 * - User must input exactly 8 digits.
 *
 * Postconditions:
 * - Returns a heap-allocated string with the user input.
 *
 * Side Effects:
 * - Interacts with the terminal, allocates memory.
 */
char *getCurrentDateML() {
    char *date = (char *)malloc(9 * sizeof(char));
    if (date == NULL) {
        printf("\nMemory allocation error.\n");
        return NULL;
    }
    printf("Enter the date (format ddmmyyyy): ");
    read(8, date);
    date[8] = '\0';
    return date;
} 

/* parseData
 * Syntax Specification:
 * void parseData(const char *date, int *day, int *month, int *year);
 *
 * Semantic Specification:
 * Parses a date string into day, month, and year components.
 *
 * Preconditions:
 * - 'date' must be a valid "ddmmyyyy" string.
 * - Output pointers must be non-null.
 *
 * Postconditions:
 * - Fills the output variables with parsed values.
 *
 * Side Effects:
 * - None.
 */
void parseData(const char *date, int *day, int *month, int *year) {
    char buffer[5];

    strncpy(buffer, date, 2);
    buffer[2] = '\0';
    *day = atoi(buffer);

    strncpy(buffer, date + 2, 2);
    buffer[2] = '\0';
    *month = atoi(buffer);

    strncpy(buffer, date + 4, 4);
    buffer[4] = '\0';
    *year = atoi(buffer);
}

/* totalDays
 * Syntax Specification:
 * int totalDays(int day, int month, int year);
 *
 * Semantic Specification:
 * Calculates the number of days from 01/01/0000 to the given date.
 *
 * Preconditions:
 * - Valid date components.
 *
 * Postconditions:
 * - Returns the total number of days.
 *
 * Side Effects:
 * - None.
 */
int totalDays(int day, int month, int year) {
    int days = 0;
    for (int y = 0; y < year; y++) {
        days += (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 366 : 365;
    }
    for (int m = 1; m < month; m++) {
        days += daysInMonth(m, year);
    }
    days += day;
    return days;
}

/* compareDates
 * Syntax Specification:
 * int compareDates(const char *date1, const char *date2);
 *
 * Semantic Specification:
 * Computes the difference in days between two dates.
 *
 * Preconditions:
 * - date1 and date2 must be in "ddmmyyyy" format.
 *
 * Postconditions:
 * - Returns a signed integer difference in days.
 *
 * Side Effects:
 * - None.
 */
int compareDates(const char *date1, const char *date2) {
    int d1, m1, y1, d2, m2, y2;
    parseData(date1, &d1, &m1, &y1);
    parseData(date2, &d2, &m2, &y2);

    int days1 = totalDays(d1, m1, y1);
    int days2 = totalDays(d2, m2, y2);

    return days1 - days2;
}

char* getLastWeekDate() {
    static char lastWeek[9];
    int day, month, year;
    
    // Estrai giorno, mese e anno dalla data di oggi
    sscanf(today, "%2d%2d%4d", &day, &month, &year);
    
    day -= 7;
    
    if (day <= 0) {
        month--;
        if (month <= 0) {
            month = 12;
            year--;
        }
        
        day += daysInMonth(month, year); 
    }
    
    sprintf(lastWeek, "%02d%02d%04d", day, month, year);
    
    return lastWeek; 
    
}