#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Save the original stdout file descriptor
    int original_stdout = dup(STDOUT_FILENO);

    // Redirect stdout to the file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting output");
        close(fd);
        return 1;
    }

    printf("This message will be written to output.txt.\n");

    // Restore the original stdout
    dup2(original_stdout, STDOUT_FILENO);
    printf("This message will appear on the console.\n");

    close(fd);
    close(original_stdout); // Clean up file descriptors
    return 0;
}
