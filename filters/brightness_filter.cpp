#include "filter.h"

// Inmulteste toate valorile cu brightness-ul (valoare intre 0 si 2)
void BrightnessFilter::applyFilter(Image *image, Image *newImage) {
    for (unsigned int i = 1; i < image->height - 1; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            newImage->matrix[i][j] = Pixel(
                image->matrix[i][j].r * this->brightness,
                image->matrix[i][j].g * this->brightness,
                image->matrix[i][j].b * this->brightness,
                image->matrix[i][j].a);
        }
    }
}