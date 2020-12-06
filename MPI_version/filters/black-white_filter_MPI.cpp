#include "../../utils/filter.h"

// Trece prin fiecare pixel si face inmultirea
void BlackWhiteFilter::applyFilter(Image *image, Image *newImage) {

    for (unsigned int i = 1; i < image->height - 1; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            unsigned int gray = 0.2126 * image->matrix[i][j].r +
                                0.7152 * image->matrix[i][j].g +
                                0.0722 * image->matrix[i][j].b;
            gray = (gray > 255) ? 255 : gray;
            newImage->matrix[i][j] = Pixel(gray, gray, gray, image->matrix[i][j].a);
        }
    }
}
