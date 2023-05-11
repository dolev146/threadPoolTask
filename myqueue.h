#ifndef MYQUEUE_H_
#define MYQUEUE_H_

extern pthread_mutex_t mutexQueue;
extern pthread_cond_t condQueue;

typedef void (*node_function_ptr)(char *, int);

struct queuenodedef
{
    struct queuenodedef *next;
    char *str_input;
    int *key;
    int *order;
    node_function_ptr fnc_ptr;
};
typedef struct queuenodedef node_t;

void enqueue(node_t *node);
node_t *dequeue();

extern node_t *head1;
extern node_t *tail1;

#endif // MYQUEUE_H