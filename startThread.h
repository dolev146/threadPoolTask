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



void *startThread(void *args);



#endif // START_THREAD_H