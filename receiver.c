/******************************************************
 * Filename: receiver.c
 * Name: Kadie Degner
 * Date: 11/10/2025
 * Description: Receives and returns a "ball" signal.
 * Note: Compile with gcc -o receiver receiver.c and run with ./receiver
 * **Run before the server to get its PID**
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
pid_t opponent_pid = 0;

int receiver_points = 0;
int server_points = 0;
const char *score_labels[] = {"0", "15", "30", "40", "Game"};

void print_score()
{
    printf("\nCURRENT SCORE = Receiver: %s | Server: %s\n\n",
           score_labels[receiver_points], score_labels[server_points]);
}

void start_next_rally()
{
    volley_count = 0;
    sleep(1);
    printf("\nNew rally begins!\n");
    kill(opponent_pid, RESERVE);
}

void check_winner()
{
    if (receiver_points == 4)
    {
        printf("Receiver wins the game!\n");
        kill(opponent_pid, SIGINT);
        exit(0);
    }
    else if (server_points == 4)
    {
        printf("Server wins the game!\n");
        kill(opponent_pid, SIGINT);
        exit(0);
    }
}

void handle_ball(int sig, siginfo_t *info, void *ucontext)
{
    opponent_pid = info->si_pid;
    volley_count++;

    printf("Received ball from PID %d (volley #%d)\n", opponent_pid, volley_count);

    // If max volleys reached, server gets the point
    if (volley_count >= MAX_VOLLEYS)
    {
        printf("Max volleys reached (%d). Server gets the point.\n", MAX_VOLLEYS);
        // add_point_to_server();
        start_next_rally();
        return;
    }

    // Random delay between 1–2 seconds
    int delay = 1 + rand() % 2;
    sleep(delay);

    if ((rand() % 100) < 15)
    {
        printf("Receiver missed the ball!\n");
        start_next_rally();
        return;
    }

    printf("Receiver returning ball to PID %d...\007\n", opponent_pid);
    kill(opponent_pid, BALL_SIGNAL);
}

int main(void)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_ball;

    srand(time(NULL));

    printf("Receiver PID: %d\n", getpid());
    printf("Waiting for serve...\n\n");

    if (sigaction(BALL_SIGNAL, &sa, NULL) == -1)
    {
        printf("Error setting up signal handler.\n");
        exit(1);
    }

    while (1)
    {
        sleep(1);
    }

    return 0;
}