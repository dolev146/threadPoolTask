#include "startThread.h"
    int k = 0;
void *startThread(void *args)
{

    while (1)
    {
        pthread_mutex_lock(&mutexQueue);

        node_t *node = dequeue();
        pthread_mutex_unlock(&mutexQueue);
        if (node == NULL)
        {
            break;
        }
        node->fnc_ptr(node->str_input, *node->key);
        while (k <= order){
            if (k == *node->order){
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
