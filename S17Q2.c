#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    pid_t pid;
    char buffer[100];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid == 0) { // Child process
        close(pipe_fd[0]); // Close read end
        char *messages[] = {"Hello World", "Hello SPPU", "Linux is Funny"};
        for (int i = 0; i < 3; i++) {
            write(pipe_fd[1], messages[i], strlen(messages[i]) + 1);
        }
        close(pipe_fd[1]);
    } else if (pid > 0) { // Parent process
        close(pipe_fd[1]); // Close write end
        printf("Parent is reading messages:\n");
        while (read(pipe_fd[0], buffer, sizeof(buffer)) > 0) {
            printf("%s\n", buffer);
        }
        close(pipe_fd[0]);
    } else {
        perror("Fork failed");
    }

    return 0;
}
