#include "filter.h"
#include <omp.h>

/* Verifica daca un pixel weak are unul strong in jur, daca da il face strong */
void EdgeTrackingFilter::applyFilter(Image *image, Image *newImage) {
    const int weak = 100;
    const int strong = 255;
    unsigned int i, j;

    /* TODO: ar trebui sa vedem cum stabilim numarul de thread-uri */
    omp_set_num_threads(omp_get_num_procs());

    #pragma omp parallel for shared(image, newImage, weak, strong) private(i, j)
        for (i = 1; i < image->height - 1; ++i) {
            for (j = 1; j < image->width - 1; ++j) {
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
