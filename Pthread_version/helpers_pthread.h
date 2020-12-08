#ifndef HELPERS_PTHREAD_H
#define HELPERS_PTHREAD_H
#include <pthread.h>

#define NUM_THREADS 4

typedef struct {
    int thread_id;
    pthread_barrier_t *barrier;
} thread_specific_data_t;

#endif /* HELPERS_PTHREAD_H */