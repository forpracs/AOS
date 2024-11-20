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
        printf("Type: ");
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

    return 0;
}
