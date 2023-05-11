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
    printf("Enter the text to be processed:\n");

    while ((c = getchar()))
    {
        if (c == EOF || c == '\n')
        {
            break;
        }
        buffer[i++] = c;

        if (i == CHUNK_SIZE)
        {
//pthread_mutex_lock(&mutexQueue);
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
           // pthread_mutex_unlock(&mutexQueue);
          //  pthread_cond_signal(&condQueue);
        }
    }
    printf("End of input\n");

    // If there are remaining characters less than CHUNK_SIZE, enqueue them
    if (i > 0)
    {
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
        //pthread_mutex_unlock(&mutexQueue);
      //  pthread_cond_signal(&condQueue);
    }

    // for (int x = 0; x < THREAD_NUM; x++)
    // {
    //     pthread_mutex_lock(&mutexQueue);
    //     enqueue(NULL);
    //     pthread_mutex_unlock(&mutexQueue);
    //     pthread_cond_signal(&condQueue);
    // }

    free(buffer);
}