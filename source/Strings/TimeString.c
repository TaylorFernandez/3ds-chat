#include "TimeString.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

char* getTime(){
    time_t unixTime = time(NULL);
    struct tm* timeStruct = gmtime((const time_t *)&unixTime);

    int hours = timeStruct->tm_hour;
    int minutes = timeStruct->tm_min;
    int seconds = timeStruct->tm_sec;
    
    char* timeStr = malloc(10 * sizeof(char));
    sprintf(timeStr, "%.2d:%.2d:%.2d", hours, minutes, seconds);

    return timeStr;
}