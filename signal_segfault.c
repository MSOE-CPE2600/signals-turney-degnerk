/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Kadie Degner
 * 
 * Brief summary of modifications: Created a signal handler for SIGSEV. When the segmentation fault occurs, the handler prints a message instead of terminating the program abruptly.
 */


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigsegv(int sig) {
    printf("Caught signal: Segmentation Fault\n");
    sleep(1); // Sleep for a moment to prevent message spamming
}

int main (int argc, char* argv[]) {
    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = &handle_sigsegv;
    sigaction(SIGSEGV, &sa, NULL);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}