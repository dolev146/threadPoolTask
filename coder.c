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
#include <errno.h>
#include "read_chunks.h"

#define THREAD_NUM 20
#define MAX_CHAR 1024

// Flag for notifying threads to exit
volatile int exit_flag = 0;


pthread_t th[THREAD_NUM];

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void (*chosen_function)(char *, int) = NULL;
int order = 0;
int key = 0;

int main(int argc, char **argv)
{
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
    read_chunks();

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

    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);

    return 0;
}