#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStat) == 0) {
            printf("File: %s\n", argv[i]);
            printf("Inode Number: %lu\n", fileStat.st_ino);
            printf("File Type: ");
            if (S_ISREG(fileStat.st_mode)) printf("Regular File\n");
            else if (S_ISDIR(fileStat.st_mode)) printf("Directory\n");
            else if (S_ISCHR(fileStat.st_mode)) printf("Character Device\n");
            else if (S_ISBLK(fileStat.st_mode)) printf("Block Device\n");
            else if (S_ISFIFO(fileStat.st_mode)) printf("FIFO\n");
            else if (S_ISLNK(fileStat.st_mode)) printf("Symbolic Link\n");
            else if (S_ISSOCK(fileStat.st_mode)) printf("Socket\n");
            else printf("Unknown\n");
        } else {
            perror("Error");
        }
    }
    return 0;
}
