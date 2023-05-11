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
        if (c == EOF || c == '\n')
        {
            break;
        }
        buffer[i++] = c;

        if (i == CHUNK_SIZE)
        {
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
        }
    }
    

    // If there are remaining characters less than CHUNK_SIZE, enqueue them
    if (i > 0)
    {
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

    }

    free(buffer);
}