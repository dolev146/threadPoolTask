#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "myqueue.h"
#include "codec.h"

#define SERVERPORT 5003
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100
#define THREAD_POOL_SIZE 20

pthread_t thread_pool[THREAD_POOL_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

char client_message[1024];

void *handle_connection(void *p_client_socket);
int check(int exp, const char *msg);
void *thread_function(void *arg);

int main(int argc, char **argv)
{

    if (argc != 3)
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


    // first off we create a bunch of threads
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, thread_function, NULL);
    }
    printf("start... \n");
    while (true)
    {

        // int *pclient = (int *)malloc(sizeof(int));
        // *pclient = client_socket;
        pthread_mutex_lock(&mutex);
        // enqueue(pclient);
        pthread_cond_signal(&condition_var);
        pthread_mutex_unlock(&mutex);
    }
}

void *thread_function(void *arg)
{
    while (true)
    {
        // mutex and cond are designed to work with each other so it is writen like that so that a mutex will not block
        // if contition doesnt met
        int *pclient;
        pthread_mutex_lock(&mutex);
        if ((pclient = dequeue()) == NULL)
        {
            pthread_cond_wait(&condition_var, &mutex);
            // try again
            pclient = dequeue();
        }
        pthread_mutex_unlock(&mutex);
        if (pclient != NULL)
        {
            // we have a connection
            handle_connection(pclient);
        }
    }
}

void *handle_connection(void *p_client_socket)
{
    int client_socket = *((int *)p_client_socket);
    free(p_client_socket);
    // char buffer[BUFSIZE] = "hi from server ";
    // recv(client_socket, client_message, 1024, 0);
    // printf("%s", client_message);
    // send(client_socket, buffer, 1024, 0);
    // close(client_socket);
    return NULL;
}

// #include "codec.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// // cat 1024.txt | ./tester 2
// // ./tester 2 < 1024.txt > out

// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 	{
// 	    printf("usage: key < file \n");
// 	    printf("!! data more than 1024 char will be ignored !!\n");
// 	    return 0;
// 	}

// 	int key = atoi(argv[1]);
// 	printf("key is %i \n",key);

// 	char c;
// 	int counter = 0;
// 	int dest_size = 1024;
// 	char data[dest_size];

// 	while ((c = getchar()) != EOF)
// 	{
// 	  data[counter] = c;
// 	  counter++;

// 	  if (counter == 1024){
// 		encrypt(data,key);
// 		printf("encripted data: %s\n",data);
// 		counter = 0;
// 	  }
// 	}

// 	if (counter > 0)
// 	{
// 		char lastData[counter];
// 		lastData[0] = '\0';
// 		strncat(lastData, data, counter);
// 		encrypt(lastData,key);
// 		printf("encripted data:\n %s\n",lastData);
// 	}

// 	return 0;
// }
