#include <stdio.h>
#include <setjmp.h>

// Declare a jump buffer
jmp_buf env;

// Global variable
int global_var = 0;

// Static variable
static int static_var = 0;

// Volatile variable
volatile int volatile_var = 0;

int main() {
    // Automatic (stack) variable
    int auto_var = 0;

    // Register variable (may not work on all systems)
    register int register_var = 0;

    // Set a jump point
    if (setjmp(env) != 0) {
        printf("After longjmp:\n");
        printf("Auto: %d\n", auto_var);
        printf("Global: %d\n", global_var);
        printf("Static: %d\n", static_var);
        printf("Register: %d\n", register_var);
        printf("Volatile: %d\n", volatile_var);
        return 0;
    }

    // Change the values of the variables
    auto_var = 1;
    global_var = 2;
    static_var = 3;
    register_var = 4;
    volatile_var = 5;

    // Simulate a non-local jump using longjmp
    longjmp(env, 1);
}
