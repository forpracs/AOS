#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct dirent *dir_entry;
    struct stat file_stat;
    DIR *directory;

    // Open the current directory
    directory = opendir(".");

    if (directory == NULL) {
        perror("Error opening current directory");
        return 1;
    }

    // Get the current year and month to filter for
    int target_year = 2023; // Replace with the desired year
    int target_month = 10;  // Replace with the desired month

    printf("Files created in %d-%02d:\n", target_year, target_month);

    while ((dir_entry = readdir(directory)) != NULL) {
        char *file_name = dir_entry->d_name;

        // Skip special directories "." and ".."
        if (strcmp(file_name, ".") == 0 || strcmp(file_name, "..") == 0) {
            continue;
        }

        // Get file attributes
        if (stat(file_name, &file_stat) == -1) {
            perror("Error getting file stat");
            continue;
        }

        // Extract year and month from the file's last modification time
        struct tm *file_time = localtime(&file_stat.st_mtime);
        int file_year = file_time->tm_year + 1900;
        int file_month = file_time->tm_mon + 1; // Months are 0-based

        if (file_year == target_year && file_month == target_month) {
            printf("%s\n", file_name);
        }
    }

    closedir(directory);

    return 0;
}
