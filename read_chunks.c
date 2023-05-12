#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "read_chunks.h"
#include "myqueue.h"

#define CHUNK_SIZE 1023

void read_chunks()
{
    char *buffer = malloc(sizeof(char) * (CHUNK_SIZE + 1));
    int c;
    int i = 0;
    while ((c = getchar()))
    {
        if (c == EOF)
        {
            break;
        }
        buffer[i++] = c;
        // printf("i: %d\n", i);
        if (i == CHUNK_SIZE)
        {
            // mutex lock
            // pthread_mutex_lock(&mutexQueue);
            // printf("got inside i: %d\n", i);
            buffer[i] = '\0';
            node_t *node = malloc(sizeof(node_t));
            node->key = malloc(sizeof(int));
            node->order = malloc(sizeof(int));
            node->str_input = malloc(sizeof(char) * (CHUNK_SIZE + 1));
            node->fnc_ptr = chosen_function;
            strcpy(node->str_input, buffer);
            *(node->key) = key;
            *(node->order) = order;
            enqueue(node);
            i = 0; // reset index
            order++;
            // clean the buffer
            memset(buffer, 0, sizeof(char) * CHUNK_SIZE + 1);
            // mutex unlock
            // pthread_mutex_unlock(&mutexQueue);
            // signal the threads
            pthread_cond_signal(&condQueue);
        }
    }
    // printf("End of input\n");

    // If there are remaining characters less than CHUNK_SIZE, enqueue them
    if (i > 0)
    {
        // mutex lock
        // pthread_mutex_lock(&mutexQueue);
        buffer[i] = '\0';
        node_t *node = malloc(sizeof(node_t));
        node->key = malloc(sizeof(int));
        node->order = malloc(sizeof(int));
        node->str_input = malloc(sizeof(char) * (CHUNK_SIZE + 1));
        node->fnc_ptr = chosen_function;
        strcpy(node->str_input, buffer);
        *(node->key) = key;
        *(node->order) = order;
        enqueue(node);
        // clean the buffer
        memset(buffer, 0, sizeof(char) * CHUNK_SIZE + 1);
        // mutex unlock
        // pthread_mutex_unlock(&mutexQueue);
        // signal the threads
        pthread_cond_signal(&condQueue);
    }


    // insert senital values
    for (int x = 0; x < THREAD_NUM; x++)
    {
        // mutex lock
        // pthread_mutex_lock(&mutexQueue);
        node_t *node = malloc(sizeof(node_t));
        node->key = malloc(sizeof(int));
        node->order = malloc(sizeof(int));
        node->str_input = malloc(sizeof(char) * (CHUNK_SIZE + 1));
        node->fnc_ptr = NULL;
        strcpy(node->str_input, "senital");
        *(node->key) = 0;
        *(node->order) = x;
        // printf("inserting senital %d\n", x);
        enqueue(node);
        // mutex unlock
        // pthread_mutex_unlock(&mutexQueue);
        // signal the threads
        pthread_cond_signal(&condQueue);
    }

    free(buffer);
}