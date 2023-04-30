// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// int buffer;
// int data_available = 0;

// void *producer(void *arg) {
//     for (int i = 0; i < 10; i++) {
//         pthread_mutex_lock(&mutex);

//         buffer = i;
//         data_available = 1;
//         printf("Producer: data %d produced\n", buffer);

//         pthread_cond_signal(&cond);
//         pthread_mutex_unlock(&mutex);

//         sleep(1);
//     }

//     return NULL;
// }

// void *consumer(void *arg) {
//     while (1) {
//         pthread_mutex_lock(&mutex);

//         while (!data_available) {
//             pthread_cond_wait(&cond, &mutex);
//         }

//         printf("Consumer: data %d consumed\n", buffer);
//         data_available = 0;

//         pthread_mutex_unlock(&mutex);
//     }

//     return NULL;
// }

// int main() {
//     pthread_t producer_thread, consumer_thread;

//     pthread_create(&producer_thread, NULL, producer, NULL);
//     pthread_create(&consumer_thread, NULL, consumer, NULL);

//     pthread_join(producer_thread, NULL);
//     pthread_join(consumer_thread, NULL);

//     pthread_mutex_destroy(&mutex);
//     pthread_cond_destroy(&cond);

//     return 0;
// }


#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    errno = 0; // Reset errno before calling sysconf
    int max_threads = sysconf(_SC_THREAD_THREADS_MAX);

    if (max_threads == -1 && errno != 0) { // Check if an error occurred
        perror("sysconf");
        printf("errno: %d\n", errno);
        return 1;
    }

    printf("Maximum number of threads: %d\n", max_threads);
    return 0;
}