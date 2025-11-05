/**
 * File: recv_signal.c
 * Modified by: Kadie Degner
 * 
 * Brief summary of program: Processes a recieved signal with siginfo_t structure to extract sender's PID and sent value.
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigusr1(int sig, siginfo_t *info, void *context) {
    int value = info->si_value.sival_int;
    pid_t sender = info->si_pid;
    printf("\nReceiver: Got SIGUSR1 from PID %d with value %d\n", sender, value);
}


int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &handle_sigusr1;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        printf("Receiver: Error setting up signal handler.\n");
        exit(1);
    }

    printf("Receiver PID: %d\n", getpid());
    printf("Receiver: Waiting for SIGUSR1...\n");
    while (1) {
        sleep(1);
    }

    return 0;
}


