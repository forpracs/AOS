#include <stdio.h>
#include <stdlib.h>

// Function to be called when the program exits
void cleanup() {
    printf("Cleanup function called. Performing cleanup tasks...\n");
    // Place your cleanup code here
}

int main() {
    // Register the cleanup function using atexit()
    if (atexit(cleanup) != 0) {
        fprintf(stderr, "Failed to register cleanup function.\n");
        return 1;
    }

    printf("Program is running...\n");

    // Simulate some program activity
    // For demonstration purposes, we'll exit the program explicitly.
    exit(0);

    // The cleanup function will be called automatically upon program exit.
}
