#include "../../utils/filter.h"
#include "../helpers_pthread.h"
#include <cmath>

float maxVal = -3.40282347e+38F;

// Imparte valorile in 2 high si low (threshold-urile sunt constante in clasa
// poate trebuiesc date ca input in caz ca se vrea)
void DoubleTresholdFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    // Calculate the maximum value for each thread
    float threadMaxVal = -3.40282347e+38F;
    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            threadMaxVal = (threadMaxVal < image->matrix[i][j].r) ? image->matrix[i][j].r : threadMaxVal;
        }
    }

    // Compare and set to get the maximum value
    pthread_mutex_lock(t_data->mutex);
    maxVal = (maxVal < threadMaxVal) ? threadMaxVal : maxVal;
    pthread_mutex_unlock(t_data->mutex);
    pthread_barrier_wait(t_data->barrier);

    float high = maxVal * this->thresholdHigh;
    float low  = high * this->thresholdLow;

    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            if (image->matrix[i][j].r >= high) {
                newImage->matrix[i][j] = Pixel(255, 255, 255, image->matrix[i][j].a);
            } else {
                if (image->matrix[i][j].r >= low) {
                    newImage->matrix[i][j] = Pixel(100, 100, 100, image->matrix[i][j].a);
                }
            }
        }
    }
}