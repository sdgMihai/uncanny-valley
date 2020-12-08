#include "../../utils/filter.h"
#include "../helpers_pthread.h"

// Aplica formula de contrast (ia valori intre -128 si 128)
void ConstrastFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    float factor = (259. * (this->contrast + 255.)) / (255. * (259. - this->contrast));
    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            Pixel newPixel;
            float tempColor;

            newPixel.a = image->matrix[i][j].a;
            tempColor = factor * (image->matrix[i][j].r - 128) + 128;
            tempColor = (tempColor < 0) ? 0 : tempColor;
            newPixel.r = (tempColor > 255) ? 255 : tempColor;
            tempColor = factor * (image->matrix[i][j].g - 128) + 128;
            tempColor = (tempColor < 0) ? 0 : tempColor;
            newPixel.g = (tempColor > 255) ? 255 : tempColor;
            tempColor = factor * (image->matrix[i][j].b - 128) + 128;
            tempColor = (tempColor < 0) ? 0 : tempColor;
            newPixel.b = (tempColor > 255) ? 255 : tempColor;

            newImage->matrix[i][j] = newPixel;
        }
    }
}
