#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    struct stat fileStat;
    if (stat(argv[1], &fileStat) == 0) {
        printf("File: %s\n", argv[1]);
        printf("Inode: %lu\n", fileStat.st_ino);
        printf("Hard Links: %lu\n", fileStat.st_nlink);
        printf("Permissions: %o\n", fileStat.st_mode & 0777);
        printf("Size: %ld bytes\n", fileStat.st_size);
        printf("Last Access: %ld\n", fileStat.st_atime);
        printf("Last Modification: %ld\n", fileStat.st_mtime);
    } else {
        perror("Error");
    }
    return 0;
}
