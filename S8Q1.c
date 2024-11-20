#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("File open error");
        return 1;
    }

    dup2(fd, STDOUT_FILENO); // Redirect stdout to file
    printf("This text will be written to output.txt\n");
    close(fd);

    return 0;
}
