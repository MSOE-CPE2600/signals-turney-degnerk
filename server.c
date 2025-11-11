/******************************************************
 * Filename: server.c
 * Name: Kadie Degner
 * Date: 11/10/2025
 * Description: Serves the first ball and plays back and forth.
 * Note: Compile with gcc -o server server.c and run with ./server <receiver_pid>
 * **Run receiver first to get its PID**
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define BALL_SIGNAL SIGUSR1
#define RESERVE SIGUSR2
#define MAX_VOLLEYS 10

int volley_count = 0;
pid_t receiver_pid;

int server_points = 0;
int receiver_points = 0;
const char *score_labels[] = {"0", "15", "30", "40", "Game"};

void print_score()
{
    printf("\nCURRENT SCORE = Server: %s | Receiver: %s\n\n",
           score_labels[server_points], score_labels[receiver_points]);
}

void start_next_rally()
{
    volley_count = 0;
    sleep(1);
    printf("New rally begins! Serving again...\a\n");
    kill(receiver_pid, BALL_SIGNAL);
}

void check_winner()
{
    if (server_points == 4)
    {
        printf("Server wins the game!\n");
        kill(receiver_pid, SIGINT);
        exit(0);
    }
    else if (receiver_points == 4)
    {
        printf("Receiver wins the game!\n");
        kill(receiver_pid, SIGINT);
        exit(0);
    }
}

void add_point_to_server()
{
    if (server_points < 4)
    {
        server_points++;
    }
    print_score();
    check_winner();
}

void add_point_to_receiver()
{
    if (receiver_points < 4)
    {
        receiver_points++;
    }
    print_score();
    check_winner();
}

void handle_reserve(int sig, siginfo_t *info, void *ucontext)
{
    volley_count = 0;
    server_points++;
    print_score();
    check_winner();
    printf("Server sending ball to PID %d...\007\n", receiver_pid);
    kill(receiver_pid, BALL_SIGNAL);
}

void handle_ball(int sig, siginfo_t *info, void *ucontext)
{
    volley_count++;
    printf("Received ball back from PID %d (volley #%d)\n", info->si_pid, volley_count);

    // If max volleys reached, receiver gets the point
    if (volley_count >= MAX_VOLLEYS)
    {
        printf("Max volleys reached (%d). Receiver gets the point.\n", MAX_VOLLEYS);
        add_point_to_receiver();
        start_next_rally();
        return;
    }

    // Random delay between 1–2 seconds
    int delay = 1 + rand() % 2;
    sleep(delay);

    if ((rand() % 100) < 15)
    {
        printf("Server missed the ball!\n");
        add_point_to_receiver();
        start_next_rally();
        return;
    }

    printf("Server sending ball to PID %d...\007\n", receiver_pid);
    kill(receiver_pid, BALL_SIGNAL);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc != 2)
    {
        printf("Error: Include a process id for a receiver\n");
        exit(1);
    }

    receiver_pid = atoi(argv[1]);

    // Setup signal handler for ball signal
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_ball;

    if (sigaction(BALL_SIGNAL, &sa, NULL) == -1)
    {
        printf("Error setting up ball signal handler\n");
        exit(1);
    }

    // Setup signal handler for reserve signal
    struct sigaction sa2;
    sa2.sa_flags = SA_SIGINFO;
    sa2.sa_sigaction = handle_reserve;

    if (sigaction(RESERVE, &sa2, NULL) == -1)
    {
        printf("Error setting up reserve signal handler\n");
        exit(1);
    }

    printf("Server PID: %d\n", getpid());
    printf("Serving first ball to PID %d...\n\n", receiver_pid);

    // Initial serve
    kill(receiver_pid, BALL_SIGNAL);

    while (1)
    {
        sleep(1);
    }

    return 0;
}
