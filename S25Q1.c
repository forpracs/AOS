#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Redirect standard output to the file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error redirecting output");
        close(fd);
        return 1;
    }

    printf("This will be written to the file output.txt\n");
    printf("Standard output is now redirected.\n");

    close(fd); // Close the file
    return 0;
}
