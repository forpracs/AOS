#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_alarm(int sig) {
    printf("Alarm is fired!\n");
}

int main() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        sleep(2);
        kill(getppid(), SIGALRM);
        exit(0);
    } else if (pid > 0) { // Parent process
        signal(SIGALRM, handle_alarm);
        pause(); // Wait for signal
    } else {
        perror("Fork failed");
    }
    return 0;
}
