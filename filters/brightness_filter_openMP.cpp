#include "filter.h"
#include <omp.h>

/* Inmulteste toate valorile cu brightness-ul (valoare intre 0 si 2) */
void BrightnessFilter::applyFilter(Image *image, Image *newImage) {
    unsigned int i, j;
    float brightness = this->brightness;

    /* TODO: ar trebui sa vedem cum stabilim numarul de thread-uri */
    omp_set_num_threads(omp_get_num_procs());

    #pragma omp parallel for shared(image, newImage, brightness) private(i, j)
        for (i = 1; i < image->height - 1; ++i) {
            for (j = 1; j < image->width - 1; ++j) {
                newImage->matrix[i][j] = Pixel(
                    image->matrix[i][j].r * brightness,
                    image->matrix[i][j].g * brightness,
                    image->matrix[i][j].b * brightness,
                    image->matrix[i][j].a);
            }
        }
}
