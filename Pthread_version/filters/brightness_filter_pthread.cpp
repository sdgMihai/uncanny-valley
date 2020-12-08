#include "../../utils/filter.h"
#include "../helpers_pthread.h"

// Inmulteste toate valorile cu brightness-ul (valoare intre 0 si 2)
void BrightnessFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            newImage->matrix[i][j] = Pixel(
                image->matrix[i][j].r * this->brightness,
                image->matrix[i][j].g * this->brightness,
                image->matrix[i][j].b * this->brightness,
                image->matrix[i][j].a);
        }
    }
}