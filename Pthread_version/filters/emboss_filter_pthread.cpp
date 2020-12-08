#include "../../utils/filter.h"
#include "../helpers_pthread.h"

static const float kernel[3][3] = {{0, 1, 0},
                                {0, 0, 0},
                                {0, -1, 0}};


// Aplica emboss exact la fel ca la gaussian
void EmbossFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            Pixel newPixel;
            float red, green, blue;
            red = green = blue = 0;
            newPixel.a = image->matrix[i][j].a;
            newPixel.r = newPixel.b = newPixel.g = 0;

            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    red   += static_cast<float>(image->matrix[i + ki][j + kj].r) * kernel[ki + 1][kj + 1];
                    green += static_cast<float>(image->matrix[i + ki][j + kj].g) * kernel[ki + 1][kj + 1];
                    blue  += static_cast<float>(image->matrix[i + ki][j + kj].b) * kernel[ki + 1][kj + 1];
                }
            }

            red = (red < 0) ? 0 : red;
            green = (green < 0) ? 0 : green;
            blue = (blue < 0) ? 0 : blue;
            newPixel.r = (red > 255) ? 255 : red;
            newPixel.g = (green > 255) ? 255 : green;
            newPixel.b = (blue > 255) ? 255 : blue;
            newImage->matrix[i][j] = newPixel;
        }
    }
}
