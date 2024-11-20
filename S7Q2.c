#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) { // Child process
        close(pipe_fd[0]); // Close read end
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        execlp("ls", "ls", "-l", NULL);
        perror("Exec failed");
        exit(1);
    } else if (pid > 0) { // Parent process
        close(pipe_fd[1]); // Close write end
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
        execlp("wc", "wc", "-l", NULL);
        perror("Exec failed");
        exit(1);
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
