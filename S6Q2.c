#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main() {
    int n, i;
    printf("Enter the number of child processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        if (fork() == 0) { // Child process
            sleep(1); // Simulate work
            return 0;
        }
    }

    struct rusage usage;
    for (i = 0; i < n; i++) {
        wait(NULL); // Wait for each child process
    }

    getrusage(RUSAGE_CHILDREN, &usage);
    printf("Cumulative User Time: %ld.%06lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("Cumulative System Time: %ld.%06lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);

    return 0;
}
