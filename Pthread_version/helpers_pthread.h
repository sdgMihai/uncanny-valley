#ifndef HELPERS_PTHREAD_H
#define HELPERS_PTHREAD_H
#include <pthread.h>

#define NUM_THREADS 4

typedef struct {
    int thread_id;
    pthread_barrier_t *barrier;
    pthread_mutex_t *mutex;
} thread_specific_data_t;

inline unsigned long thread_max( unsigned long a, unsigned long b)
{
	return (a > b) ? a : b;
}

#endif /* HELPERS_PTHREAD_H */