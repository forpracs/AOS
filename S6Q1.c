#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main() {
    char month[10];
    printf("Enter the month (e.g., Jan, Feb): ");
    scanf("%s", month);

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            struct tm *timeinfo = localtime(&fileStat.st_ctime);
            char file_month[4];
            strftime(file_month, sizeof(file_month), "%b", timeinfo);
            if (strcmp(file_month, month) == 0) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
