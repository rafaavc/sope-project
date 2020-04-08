#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_STRING_SIZE 1024

extern char * logFilename;
char str[MAX_STRING_SIZE];
int fd;
struct timespec start;

char * eventStrings[7] = {"CREATE", "EXIT", "RECV_SIGNAL", "SEND_SIGNAL", "RECV_PIPE", "SEND_PIPE", "ENTRY"};

void openLogFile() {
    close(open(logFilename, O_WRONLY | O_TRUNC | O_CREAT, 0644));
    fd = open(logFilename, O_WRONLY | O_APPEND);
    if (fd == -1) {
        printf("Error opening log file.\n");
        terminateProcess(1);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
}

void logMessage(char * message) {
    sprintf(str, "%s", message);
    if (write(fd, str, strlen(str)) < 0) {
        printf("Error writing to log file.\n");
        terminateProcess(1);
    }
}

void closeLog(){
    close(fd);
}

void logEVENT(enum EVENT event, int pid, char * info) {
    char * message = malloc(MAX_STRING_SIZE);

    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    double instant = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000)/1000;

    sprintf(message, "%.2lf - %-8d - %s - %s\n", instant, pid, eventStrings[event], info);
    logMessage(message);
}

void terminateProcess(int status) {
    char statuss[2];
    sprintf(statuss, "%d", status);
    logEVENT(EXIT, getpid(), statuss);
    closeLog();
    exit(status);
}
