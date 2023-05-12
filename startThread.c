#include "startThread.h"
int k = 0;
void *startThread(void *args)
{

    while (1)
    {
        pthread_mutex_lock(&mutexQueue);

        node_t *node = dequeue();
        pthread_mutex_unlock(&mutexQueue);

        // check if node is null then wait
        if (node == NULL)
        {
            pthread_mutex_lock(&mutexQueue);
            pthread_cond_wait(&condQueue, &mutexQueue);
            pthread_mutex_unlock(&mutexQueue);
            continue;
        }

        // check for node with senital str input
        if (strcmp(node->str_input, "senital") == 0)
        {
            pthread_mutex_lock(&mutexQueue);
            // printf("Thread dies %d: %s\n", *(node->order), node->str_input);
            pthread_mutex_unlock(&mutexQueue);
            break;
        }

        node->fnc_ptr(node->str_input, *node->key);
        while (k <= order)
        {
            if (k == *node->order)
            {
                pthread_mutex_lock(&mutexQueue);
                printf("%s", node->str_input);
                free(node);
                k++;
                pthread_mutex_unlock(&mutexQueue);
                break;
            }
        }
    }
    return NULL;
}
