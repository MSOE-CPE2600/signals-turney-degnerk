/**
 * File: send_signal.c
 * Modified by: Kadie Degner
 * 
 * Brief summary of program: Sends a SIGUSR1 signal with a random integer value to a specified process ID.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Missing process id argument.\n");
    }

    pid_t pid = (pid_t)atoi(argv[1]);
    srand((unsigned)time(NULL));
    int random_value = rand() % 1000;

    union sigval val;
    val.sival_int = random_value;

    if (sigqueue(pid, SIGUSR1, val) == -1) {
        printf("Error sending signal.\n");
        exit(1);
    }

    printf("Sender PID: %d\n", getpid());
    printf("SIGUSR1 signal sent to process %d with value %d\n", pid, random_value);
    return 0;
}