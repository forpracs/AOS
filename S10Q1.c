#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) { // First child process
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipe_fd[0]); // Close unused read end
        execlp("ls", "ls", "-l", NULL);
        perror("Exec failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Second child process
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipe_fd[1]); // Close unused write end
        execlp("wc", "wc", "-l", NULL);
        perror("Exec failed");
        exit(1);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
