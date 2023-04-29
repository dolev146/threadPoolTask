#include "myqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_t *head = NULL;
node_t *tail = NULL;

void enqueue(node_t *node)
{
    node_t *newnode = malloc(sizeof(node_t));
    newnode->command = malloc(1024 * sizeof(char));
    strcpy(newnode->command, node->command);
    newnode->execute = node->execute;
    newnode->next = NULL;
    if (tail == NULL)
    {
        head = newnode;
    }
    else
    {
        tail->next = newnode;
    }
    tail = newnode;
    free(node);
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