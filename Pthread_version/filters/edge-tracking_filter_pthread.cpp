#include "../../utils/filter.h"
#include "../helpers_pthread.h"

// Verifica daca un pixel weak are unul strong in jur, daca da il face strong
void EdgeTrackingFilter::applyFilter(Image *image, Image *newImage) {
    const int weak = 100;
    const int strong = 255;
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            if (image->matrix[i][j].r == weak) {
                if (image->matrix[i - 1][j - 1].r == strong || image->matrix[i - 1][j].r == strong ||
                    image->matrix[i - 1][j + 1].r  == strong || image->matrix[i][j - 1].r == strong ||
                    image->matrix[i][j + 1].r == strong || image->matrix[i + 1][j - 1].r == strong ||
                    image->matrix[i + 1][j].r == strong || image->matrix[i + 1][j + 1].r == strong) {

                    newImage->matrix[i][j] = Pixel(strong, strong, strong, image->matrix[i][j].a);
                } else {
                    newImage->matrix[i][j] = Pixel(0, 0, 0, image->matrix[i][j].a);
                }
            } else {
                newImage->matrix[i][j] = image->matrix[i][j];
            }
        }
    }
}