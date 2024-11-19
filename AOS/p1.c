#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    off_t hole_size = 1024 * 1024; // 1 MB hole size

    // Open a file for writing (or create it if it doesn't exist)
    fd = open("file_with_hole.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Seek to the desired position to create a hole
    if (lseek(fd, hole_size - 1, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write a single byte to create the hole
    char hole_data = 'A';
    if (write(fd, &hole_data, 1) != 1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // Close the file
    close(fd);

    printf("File with hole created successfully.\n");
    return 0;
}
