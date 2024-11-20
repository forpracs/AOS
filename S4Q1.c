#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStat) == 0) {
            printf("File %s is present in the current directory.\n", argv[i]);
        } else {
            printf("File %s is NOT present in the current directory.\n", argv[i]);
        }
    }
    return 0;
}
