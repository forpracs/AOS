#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char name[256];
    off_t size;
} FileInfo;

int compare(const void *a, const void *b) {
    FileInfo *file1 = (FileInfo *)a;
    FileInfo *file2 = (FileInfo *)b;
    return (file1->size - file2->size);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }

    FileInfo files[argc - 1];
    struct stat fileStat;

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStat) == 0) {
            strcpy(files[i - 1].name, argv[i]);
            files[i - 1].size = fileStat.st_size;
        } else {
            perror(argv[i]);
            return 1;
        }
    }

    qsort(files, argc - 1, sizeof(FileInfo), compare);

    printf("Files in ascending order by size:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s: %ld bytes\n", files[i].name, files[i].size);
    }

    return 0;
}
