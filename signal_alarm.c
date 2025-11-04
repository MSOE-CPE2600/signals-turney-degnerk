/**
 * File: signal_alarm.c
 * Modified by: Kadie Degner
 * 
 * Brief summary of program: Schedules an alarm to be to be sent to after 5 seconds.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void alarm_handler(int signum) {
    printf("Alarm signal received!\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = &alarm_handler;
    sigaction(SIGALRM, &sa, NULL);

    printf("Setting an alarm for 5 seconds...\n");
    alarm(5);

    while(1) {
        sleep(1);
        printf("Waiting...\n");
    }

    return 0;
}