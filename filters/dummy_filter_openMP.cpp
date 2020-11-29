#include "filter.h"
#include <omp.h>
#include <iostream>

/* Copiaza imagine */
void DummyFilter::applyFilter(Image *image, Image *newImage) {
    unsigned int i, j;

    /* TODO: ar trebui sa vedem cum stabilim numarul de thread-uri */
    omp_set_num_threads(omp_get_num_procs());

    #pragma omp parallel for shared(image, newImage) private(i, j)
        for (i = 1; i < image->height - 1; ++i) {
            for (j = 1; j < image->width - 1; ++j) {
                newImage->matrix[i][j] = image->matrix[i][j];
            }
        }
}
