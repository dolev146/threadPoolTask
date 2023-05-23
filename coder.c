#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.h"
#include "codec.h"
#include "startThread.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "read_chunks.h"

#define MAX_CHAR 1024

int cpu_count;
int THREAD_NUM;
pthread_t *th;

// Flag for notifying threads to exit
volatile int exit_flag = 0;

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void (*chosen_function)(char *, int) = NULL;
int order = 0;
int key = 0;

int main(int argc, char **argv)
{
    cpu_count = sysconf(_SC_NPROCESSORS_CONF);
    THREAD_NUM = 40;
    th = malloc(sizeof(pthread_t) * THREAD_NUM);
    if (th == NULL)
    {
        perror("Failed to allocate memory for threads");
        exit(1);
    }
    // printf("CPU count: %d\n", cpu_count);
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);

    if (argc < 3)
    {
        printf("error not valid amount of  arguments need a key and a flag\n");
        printf("for example ./coder 12 -e \n");
        return 0;
    }

    // check that the flag is valid (e or d)
    if (strcmp(argv[2], "-e") != 0 && strcmp(argv[2], "-d") != 0)
    {
        printf("error not valid flag\n");
        printf("for example ./coder 12 -e \n");
        return 0;
    }

    // check if the flag is -e or -d
    if (strcmp(argv[2], "-e") == 0)
    {
        chosen_function = &encrypt;
    }
    else if (strcmp(argv[2], "-d") == 0)
    {
        chosen_function = &decrypt;
    }

    // check if the key is a number if not print error but if the key is '0' dont throw an error
    if (atoi(argv[1]) == 0 && strcmp(argv[1], "0") != 0)
    {
        printf("error not valid key\n");
        printf("for example ./coder 12 -e \n");
        return 0;
    }

    key = atoi(argv[1]);

    // printf("key: %d\n", key);
    // printf("flag: %s\n", argv[2]);

    // create a thread pool
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0)
        {
            printf("error creating thread\n");
            perror("Failed to create thread");
            exit(1);
        }
    }

    read_chunks();

    // wait for all threads to finish
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("error joining thread\n");
            perror("Failed to join thread");
            exit(1);
        }
    }

    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);


    free(th);
    return 0;
}