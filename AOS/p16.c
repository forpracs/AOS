#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int parent_to_child_pipe[2]; // Pipe for parent to child communication
    int child_to_parent_pipe[2]; // Pipe for child to parent communication
    pid_t child_pid;

    // Create the parent-to-child pipe
    if (pipe(parent_to_child_pipe) == -1) {
        perror("pipe (parent_to_child)");
        exit(1);
    }

    // Create the child-to-parent pipe
    if (pipe(child_to_parent_pipe) == -1) {
        perror("pipe (child_to_parent)");
        exit(1);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process

        close(parent_to_child_pipe[1]); // Close the write end of the parent-to-child pipe
        close(child_to_parent_pipe[0]); // Close the read end of the child-to-parent pipe

        char message_from_parent[100];
        char message_to_parent[] = "Hello, Parent!";

        // Read from the parent-to-child pipe
        int bytes_read = read(parent_to_child_pipe[0], message_from_parent, sizeof(message_from_parent));
        if (bytes_read == -1) {
            perror("read (child)");
            exit(1);
        }

        printf("Child received from Parent: %.*s\n", bytes_read, message_from_parent);

        // Write to the child-to-parent pipe
        if (write(child_to_parent_pipe[1], message_to_parent, sizeof(message_to_parent)) == -1) {
            perror("write (child)");
            exit(1);
        }

        // Close the remaining pipe ends
        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);
    } else {
        // Parent process

        close(parent_to_child_pipe[0]); // Close the read end of the parent-to-child pipe
        close(child_to_parent_pipe[1]); // Close the write end of the child-to-parent pipe

        char message_to_child[] = "Hello, Child!";
        char message_from_child[100];

        // Write to the parent-to-child pipe
        if (write(parent_to_child_pipe[1], message_to_child, sizeof(message_to_child)) == -1) {
            perror("write (parent)");
            exit(1);
        }

        // Read from the child-to-parent pipe
        int bytes_read = read(child_to_parent_pipe[0], message_from_child, sizeof(message_from_child));
        if (bytes_read == -1) {
            perror("read (parent)");
            exit(1);
        }

        printf("Parent received from Child: %.*s\n", bytes_read, message_from_child);

        // Close the remaining pipe ends
        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);
    }

    return 0;
}
