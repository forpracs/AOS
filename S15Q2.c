#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    if (sig == SIGHUP) {
        printf("Child received SIGHUP\n");
    } else if (sig == SIGINT) {
        printf("Child received SIGINT\n");
    } else if (sig == SIGQUIT) {
        printf("My DADDY has Killed me!!!\n");
        exit(0);
    }
}

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        signal(SIGHUP, handle_signal);
        signal(SIGINT, handle_signal);
        signal(SIGQUIT, handle_signal);

        while (1) {
            sleep(1);
        }
    } else if (pid > 0) { // Parent process
        sleep(1);
        for (int i = 0; i < 5; i++) {
            kill(pid, SIGHUP);
            sleep(3);
            kill(pid, SIGINT);
            sleep(3);
        }
        kill(pid, SIGQUIT);
    } else {
        perror("Fork failed");
    }

    return 0;
}
