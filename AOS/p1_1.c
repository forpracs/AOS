#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open a file for writing, creating it if it doesn't exist 
    int fd = open("sparsefile.txt", O_WRONLY | O_CREAT, 0666);
    
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Seek to a position in the file (creating a hole)
    off_t offset = 1024 * 1024; // 1 MB offset
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write some data at the new position
    char data[] = "Hello, this is data in the hole!";
    ssize_t bytes_written = write(fd, data, sizeof(data));

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}
In this code:

We open a file named "sparsefile.txt" for writing, with the O_CREAT flag to create it if it doesn't exist and 0666 as the file permissions.

We use lseek() to move the file pointer to a specific offset (in this case, 1 MB from the beginning of the file), creating a hole in the file.

We then write some data to the file at that position, which will only occupy space on disk for the data written (i.e., it won't fill the hole).

This code creates a sparse file with a hole in it. When you check the size of the resulting file on disk, it will be larger than the actual data written due to the hole.





