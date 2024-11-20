#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        printf("Child process running...\n");
        exit(5); // Exit with status 5
    } else if (pid > 0) { // Parent process
        int status;
        wait(&status); // Wait for child process
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        perror("Fork failed");
    }
    return 0;
}
