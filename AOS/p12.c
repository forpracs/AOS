#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// Comparison function for sorting directory names alphabetically
int compareDirNames(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    int dirCount = 0; // Variable to count subdirectories

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Create an array to store subdirectory names
    char **dirNames = NULL;

    // Iterate through directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Allocate memory for the directory name and store it in the array
            char *dirName = strdup(entry->d_name);
            if (dirName != NULL) {
                dirNames = (char **)realloc(dirNames, (dirCount + 1) * sizeof(char *));
                if (dirNames != NULL) {
                    dirNames[dirCount++] = dirName;
                }
            }
        }
    }

    // Sort the subdirectory names alphabetically
    qsort(dirNames, dirCount, sizeof(char *), compareDirNames);

    // Display the sorted subdirectory names
    printf("Subdirectories in alphabetical order:\n");
    for (int i = 0; i < dirCount; i++) {
        printf("%s\n", dirNames[i]);
        free(dirNames[i]); // Free allocated memory for each name
    }

    // Free the array of directory names
    free(dirNames);

    // Close the directory
    closedir(dir);

    return 0;
}
