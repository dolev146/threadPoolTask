#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.h"
#include "codec.h"
#include <errno.h>

#define MAX_CHAR 1024

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;
int taskCount = 0;

int main(int argc, char **argv)
{
    int key;

    void (*chosen_function)(char *, int) = NULL;
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

    // read from stdin and enqueue the input to the queue in chunks of 1024 bytes
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;
    char *buffer = malloc(MAX_CHAR * sizeof(char));
    while ((read = getline(&line, &len, stdin)) != -1)
    {
        for (ssize_t i = 0; i < read; i++)
        {
            buffer[count] = line[i];
            count++;
            if (count == MAX_CHAR)
            {
                pthread_mutex_lock(&mutexQueue);
                enqueue(buffer);
                int taskCount = 0;
                pthread_mutex_unlock(&mutexQueue);
                pthread_cond_signal(&condQueue);
                count = 0;
                buffer = malloc(MAX_CHAR * sizeof(char));
            }
        }
    }
}