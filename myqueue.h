#ifndef MYQUEUE_H_
#define MYQUEUE_H_

typedef void (*ExecuteCommand)(char *, int);

struct queuenodedef
{
    struct queuenodedef *next;
    char *command;
    int *key;
    int *order;
    ExecuteCommand execute;
};

typedef struct queuenodedef node_t;
void enqueue(node_t *node);
node_t *dequeue();

extern node_t *head;
extern node_t *tail;

#endif // MYQUEUE_H