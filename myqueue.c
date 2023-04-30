#include "myqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_t *head = NULL;
node_t *tail = NULL;

void enqueue(node_t *node)
{

    printf("enqueue %s\n", node->command);
    if (tail == NULL)
    {
        head = node;
    }
    else
    {
        tail->next = node;
    }
    tail = node;
}

// return the value
node_t *dequeue()
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        node_t *result = head;
        // node_t *temp = head;
        head = head->next;
        if (head == NULL)
        {
            tail = NULL;
        }
        // free(temp); // TODO: free the memory of the command
        // i can write here logic to execute the command if i want TODO
        return result;
    }
}