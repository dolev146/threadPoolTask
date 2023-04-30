#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.h"
#include "codec.h"

#define THREAD_POOL_SIZE 20

pthread_t thread_pool[THREAD_POOL_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

char client_message[1024];

int check(int exp, const char *msg);
void *thread_function(void *arg);

int main(int argc, char **argv)
{
    int order = 0;
    // create a function pointer to store the chosend command
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
        chosen_function = encrypt;
    }
    else if (strcmp(argv[2], "-d") == 0)
    {
        chosen_function = decrypt;
    }

    // first off we create a bunch of threads
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }

    int key = atoi(argv[1]);
    char c;
    char *data = NULL;
    int data_len = 0;

    while (true)
    {

        pthread_mutex_lock(&mutex);
        order++;
        while ((c = getchar()) != EOF)
        {
            if (c == EOF || c == '\n' || c == '\r' || c == '\0' || c == '\t' || c == '\v' || c == '\f')
            {
                break;
            }

            char *new_data = realloc(data, data_len + 1);
            if (new_data == NULL)
            {
                // Handle memory allocation failure
                fprintf(stderr, "Error: Memory allocation failed.\n");
                free(data);
                exit(EXIT_FAILURE);
            }
            else
            {
                data = new_data;
                data[data_len++] = c;
            }
        }

        // Split the data into chunks of 1024 and enqueue each chunk separately
        for (int i = 0; i < data_len; i += 1023)
        {
            char chunk[1024];
            int chunk_size = 1023;
            if (data_len - i < 1023)
            {
                chunk_size = data_len - i;
            }

            strncpy(chunk, &data[i], chunk_size);
            if (chunk_size < 1024)
            {
                chunk[chunk_size] = '\0';
            }
            else
            {
                chunk[1023] = '\0';
            }

            node_t *node = (node_t *)malloc(sizeof(node_t));
            node->command = (char *)malloc(sizeof(char) * 1024);
            node->key = (int *)malloc(sizeof(int));
            node->order = (int *)malloc(sizeof(int));
            *node->order = order;
            node->execute = chosen_function;
            *node->key = key;
            node->next = NULL;
            strcpy(node->command, chunk);
            enqueue(node);
        }

        free(data);
        data = NULL;
        data_len = 0;
        pthread_cond_broadcast(&condition_var);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

void *thread_function(void *arg)
{
    int order = 0;
    while (true)
    {
        // mutex and cond are designed to work with each other so it is writen
        // like that so that a mutex will not block
        // if contition doesnt met
        node_t *node;
        pthread_mutex_lock(&mutex);
        if ((node = dequeue()) == NULL)
        {
            pthread_cond_wait(&condition_var, &mutex);
            node = dequeue();
            order++;
        }
        pthread_mutex_unlock(&mutex);
        if (node != NULL)
        {
            if (order == *node->order)
            {
                node->execute(node->command, *node->key);
                printf("after execution : %s \n", node->command);
                free(node->command);
                free(node->key);
                free(node->order);
                free(node);
                order++;
            }
        }
    }
}
