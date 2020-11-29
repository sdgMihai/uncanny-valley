#include "filter.h"
#include <omp.h>

/* Aplica formula de contrast (ia valori intre -128 si 128) */
void ConstrastFilter::applyFilter(Image *image, Image *newImage) {
    float factor = (259. * (this->contrast + 255.)) / (255. * (259. - this->contrast));
    unsigned int i, j;

    /* TODO: ar trebui sa vedem cum stabilim numarul de thread-uri */
    omp_set_num_threads(omp_get_num_procs());

    #pragma omp parallel for shared(image, newImage, factor) private(i, j)
        for (i = 1; i < image->height - 1; ++i) {
            for (j = 1; j < image->width - 1; ++j) {
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
