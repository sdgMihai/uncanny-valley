#include "../../utils/filter.h"
#include <cmath>

// Imparte valorile in 2 high si low (threshold-urile sunt constante in clasa
// poate trebuiesc date ca input in caz ca se vrea)
void DoubleTresholdFilter::applyFilter(Image *image, Image *newImage) {
    float maxVal = -MAXFLOAT;

    for (unsigned int i = 1; i < image->height - 1; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            maxVal = (maxVal < image->matrix[i][j].r) ? image->matrix[i][j].r : maxVal;
        }
    }

    float high = maxVal * this->thresholdHigh;
    float low  = high * this->thresholdLow;

    for (unsigned int i = 1; i < image->height - 1; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
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