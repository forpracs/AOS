#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int count = 0;

void handle_sigint(int sig) {
    count++;
    if (count == 1) {
        printf("Caught SIGINT (Ctrl+C), press again to exit.\n");
    } else {
        printf("Exiting...\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, handle_sigint);
    while (1) {
        printf("Running... Press Ctrl+C to interrupt.\n");
        sleep(1);
    }
    return 0;
}
