#include "filter.h"
#include <omp.h>

/* Trece prin fiecare pixel si face inmultirea */
void BlackWhiteFilter::applyFilter(Image *image, Image *newImage) {
    unsigned int i, j;

    /* TODO: ar trebui sa vedem cum stabilim numarul de thread-uri */
    omp_set_num_threads(omp_get_num_procs());

    #pragma omp parallel for shared(image, newImage) private(i, j)
        for (i = 1; i < image->height - 1; ++i) {
            for (j = 1; j < image->width - 1; ++j) {
                unsigned int gray = 0.2126 * image->matrix[i][j].r +
                                    0.7152 * image->matrix[i][j].g +
                                    0.0722 * image->matrix[i][j].b;
                gray = (gray > 255) ? 255 : gray;
                newImage->matrix[i][j] = Pixel(gray, gray, gray, image->matrix[i][j].a);
            }
        }
}
