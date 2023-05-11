#ifndef START_THREAD_H_
#define START_THREAD_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include "myqueue.h"
#include "read_chunks.h"


// Flag for notifying threads to exit
extern volatile int exit_flag;

void *startThread(void *args);



#endif // START_THREAD_H