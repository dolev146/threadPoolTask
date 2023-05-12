#include "myqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_t *head1 = NULL;
node_t *tail1 = NULL;

void enqueue(node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    node->next = NULL;
    if (tail1 == NULL)
    {
        head1 = node;
    }
    else
    {
        tail1->next = node;
    }
    tail1 = node;
}

// return the value
node_t *dequeue()
{
    if (head1 == NULL)
    {
        return NULL;
    }
    else
    {
        node_t *result = head1;
        head1 = head1->next;
        if (head1 == NULL)
        {
            tail1 = NULL;
        }
        return result;
    }
}
