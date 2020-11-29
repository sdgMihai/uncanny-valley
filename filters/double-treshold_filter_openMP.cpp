#include "filter.h"
#include <cmath>
#include <omp.h>

/**
 * Imparte valorile in 2 high si low (threshold-urile sunt
 * constante in clasa poate trebuiesc date ca input in caz ca se vrea)
 */
void DoubleTresholdFilter::applyFilter(Image *image, Image *newImage) {
    float maxVal = -MAXFLOAT;

    unsigned int i, j;

    for (i = 1; i < image->height - 1; ++i) {
        for (j = 1; j < image->width - 1; ++j) {
            maxVal = (maxVal < image->matrix[i][j].r) ? image->matrix[i][j].r : maxVal;
        }
    }

    float high = maxVal * this->thresholdHigh;
    float low  = high * this->thresholdLow;

    /* TODO: ar trebui sa vedem cum stabilim numarul de thread-uri */
    omp_set_num_threads(omp_get_num_procs());

    #pragma omp parallel for shared(image, newImage, high, low) private(i, j)
        for (i = 1; i < image->height - 1; ++i) {
            for (j = 1; j < image->width - 1; ++j) {
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
