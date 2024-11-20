#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

void handle_alarm(int sig) {
    printf("Child did not finish in time, killing it.\n");
    kill(child_pid, SIGKILL);
}

void handle_child_termination(int sig) {
    printf("Child terminated.\n");
}

int main() {
    signal(SIGCHLD, handle_child_termination);
    signal(SIGALRM, handle_alarm);

    child_pid = fork();
    if (child_pid == 0) { // Child process
        execlp("sleep", "sleep", "10", NULL); // Simulate a long-running process
        perror("Exec failed");
        exit(1);
    } else if (child_pid > 0) { // Parent process
        alarm(5); // Set an alarm for 5 seconds
        wait(NULL); // Wait for child process
    } else {
        perror("Fork failed");
    }
    return 0;
}
