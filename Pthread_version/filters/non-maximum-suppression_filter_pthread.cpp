#include "../../utils/filter.h"
#include "../helpers_pthread.h"

// Se foloseste de theta calculat in gradient ca sa modifice pixelii
void NonMaximumSuppressionFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            float q = 255;
            float r = 255;
            if ((0 <= theta[i][j] && theta[i][j] < 22.5) || (157.5 <= theta[i][j] && theta[i][j] <= 180))  { 
                q = image->matrix[i][j + 1].r;
                r = image->matrix[i][j - 1].r; 
            } else {
                if ((22.5 <= theta[i][j] && theta[i][j] < 67.5)) {
                    q = image->matrix[i + 1][j - 1].r;
                    r = image->matrix[i - 1][j + 1].r;
                } else {
                    if ((67.5 <= theta[i][j] && theta[i][j] < 112.5)) {
                        q = image->matrix[i + 1][j].r;
                        r = image->matrix[i - 1][j].r;
                    } else {
                        if ((112.5 <= theta[i][j] && theta[i][j] < 157.5)) {
                            q = image->matrix[i - 1][j - 1].r;
                            r = image->matrix[i + 1][j + 1].r;
                        }
                    }
                }
            }
            Pixel newPixel;
            newPixel.a = image->matrix[i][j].a;
            if (image->matrix[i][j].r >= q && image->matrix[i][j].r >= r) {
                newPixel.r =  newPixel.g = newPixel.b = image->matrix[i][j].r;
            } else {
                newPixel.r =  newPixel.g = newPixel.b = 0;
            }
            newImage->matrix[i][j] = newPixel;
        }
    }
}
