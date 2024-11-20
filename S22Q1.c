#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    struct dirent *entry;
    int found = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, argv[1]) == 0) {
            found = 1;
            break;
        }
    }

    closedir(dir);

    if (found) {
        printf("File '%s' is present in the current directory.\n", argv[1]);
    } else {
        printf("File '%s' is NOT present in the current directory.\n", argv[1]);
    }

    return 0;
}
