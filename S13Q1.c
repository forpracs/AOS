#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_stop(int sig) {
    printf("Process suspended. Send SIGCONT to resume.\n");
    pause(); // Wait until resumed
}

void handle_continue(int sig) {
    printf("Process resumed.\n");
}

int main() {
    signal(SIGTSTP, handle_stop); // Ctrl+Z
    signal(SIGCONT, handle_continue);

    while (1) {
        printf("Running... Press Ctrl+Z to suspend.\n");
        sleep(1);
    }

    return 0;
}
