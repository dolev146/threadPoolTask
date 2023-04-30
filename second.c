#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "myqueue.h"
#include "codec.h"



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
#define MAX_CHUNK_SIZE 1024
#define MAX_THREADS 20

char buffer[1024];
int data_available = 0;

void *producer(void *arg) {
    // read data with getchar() dynamically and insert into queue with enqueue() in chunks of 1023 bytes 
    // (the last byte is for the null terminator)
    while (1) {
        pthread_mutex_lock(&mutex);
        memset(buffer, 0, 1024);
        // devide the data into chunks of 1023 bytes (the last byte is for the null terminator) and insert into queue with enqueue()
        int i = 0;
        while (i < 3) {
            char c = getchar();
            if (c == EOF) {
                break;
            }
            buffer[i] = c;
            i++;
        }
        node_t *node = malloc(sizeof(node_t));
        node->command = malloc(sizeof(char) * 1024);
        strcpy(node->command, buffer);
        enqueue(node);
        data_available = 1;
        printf("Producer: data %s produced\n", buffer);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        // sleep(1);
    }

    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex2);

        while (!data_available) {
            pthread_cond_wait(&cond, &mutex2);
        }

        node_t *node = dequeue();
        printf("Consumer: data %s consumed\n", node->command);
        data_available = 0;



        pthread_mutex_unlock(&mutex2);
    }

    return NULL;
}

int main() {
    // init 1 thread for producder and the rest for consumer
    pthread_t producer_thread, consumer_thread[MAX_THREADS - 1];

    pthread_create(&producer_thread, NULL, producer, NULL);


    // init 19 threads for consumer
    for (int i = 0; i < MAX_THREADS - 1; i++) {
        pthread_create(&consumer_thread[i], NULL, consumer, NULL);
    }


    pthread_join(producer_thread, NULL);
    for (int i = 0; i < MAX_THREADS - 1; i++) {
        pthread_join(consumer_thread[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
