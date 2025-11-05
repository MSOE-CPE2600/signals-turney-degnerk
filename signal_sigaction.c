/**
 * File: sigaction.c
 * Modified by: Kadie Degner.
 * 
 * Brief summary of program: Uses sigaction to register a signalh 
 * handler that provides information when SIGUSR1 is recieved.
 * 
 * Note: Command to send SIGUSR1 to this process from another terminal:
 *  kill -SIGUSR1 <PID>
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void handle_sigusr1(int sig, siginfo_t *siginfo, void *context) {
    printf("Received SIGUSR1\n");
    printf("Signal: %d\n", siginfo->si_signo);
    printf("Sender PID: %d\n", siginfo->si_pid);
    printf("Sender UID: %d\n", siginfo->si_uid);
    return;
}


int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &handle_sigusr1;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        printf("Error setting up sigaction.\n");
        exit(1);
    }

    printf("Process PID: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    while (1) {
        sleep(1);
    }

    return 0;
}