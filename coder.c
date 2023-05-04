#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.h"
#include "codec.h"

int main()
{
    long max_threads = sysconf(_SC_THREAD_THREADS_MAX);

    if (max_threads == -1)
    {
        printf("Error: The maximum number of threads is indeterminate.\n");
        return 1;
    }

    printf("Maximum number of threads according to POSIX: %ld\n", max_threads);
    return 0;
}