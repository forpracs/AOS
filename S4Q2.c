#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int signum) {
    if (signum == SIGHUP) {
        printf("Child: Received SIGHUP\n");
    } else if (signum == SIGINT) {
        printf("Child: Received SIGINT\n");
    } else if (signum == SIGQUIT) {
        printf("Child: Received SIGQUIT\n");
        printf("My Papa has Killed me!!!\n");
        exit(0);
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        // Set up the signal handler for SIGHUP, SIGINT, and SIGQUIT
        signal(SIGHUP, signal_handler);
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);

        // Child process waits to receive signals
        while (1) {
            pause(); // Wait for signals
        }
    } else { // Parent process
        // Send signals to the child process every 3 seconds
        for (int i = 1; i <= 5; i++) {
            sleep(3);
            if (i % 2 == 1) {
                kill(pid, SIGHUP);
            } else {
                kill(pid, SIGINT);
            }
        }
        
        // After 15 seconds, send SIGQUIT to the child process
        kill(pid, SIGQUIT);

        // Wait for the child to terminate
        wait(NULL);
    }

    return 0;
}
