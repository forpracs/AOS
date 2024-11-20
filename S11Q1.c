#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;

    // Get current file size limit
    getrlimit(RLIMIT_FSIZE, &limit);
    printf("Current file size limit: Soft = %ld, Hard = %ld\n", limit.rlim_cur, limit.rlim_max);

    // Set a new file size limit
    limit.rlim_cur = 1024 * 1024; // 1 MB
    setrlimit(RLIMIT_FSIZE, &limit);

    // Get updated file size limit
    getrlimit(RLIMIT_FSIZE, &limit);
    printf("Updated file size limit: Soft = %ld, Hard = %ld\n", limit.rlim_cur, limit.rlim_max);

    return 0;
}
