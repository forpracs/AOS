#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT); // Block Ctrl+C
    sigaddset(&set, SIGQUIT); // Block Ctrl+\
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == 0) { // First child
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("Exec failed");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Second child
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("Exec failed");
        exit(1);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    block_signals(); // Block Ctrl+C and Ctrl+\ signals
    wait(NULL);
    wait(NULL);

    return 0;
}
