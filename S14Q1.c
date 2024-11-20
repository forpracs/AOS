#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    long n;
    printf("Enter the size in bytes: ");
    scanf("%ld", &n);

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;
    printf("Files larger than %ld bytes:\n", n);
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0 && fileStat.st_size > n) {
            printf("%s (%ld bytes)\n", entry->d_name, fileStat.st_size);
        }
    }

    closedir(dir);
    return 0;
}
