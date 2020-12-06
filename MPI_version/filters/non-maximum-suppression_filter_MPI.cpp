#include "../../utils/filter.h"

// Se foloseste de theta calculat in gradient ca sa modifice pixelii
void NonMaximumSuppressionFilter::applyFilter(Image *image, Image *newImage) {
    ASSERT(theta != NULL);
    ASSERT(theta[i] != NULL);
    // printf("\n\nin nonmaxtheta-height: %u theta width %u theta:%p\n", thetaHeight, thetaWidth, theta);
    // printf("in nonmaximage -height: %u  width %u image:%p\n", image->height, image->width, image->matrix);
    // // for(unsigned int i = 0; i < image->height; ++i) {
    //     for(unsigned int j = 0; j < image->width; ++j) {
    //         printf("[%u][%u] %u ",i, j, image->matrix[i][j].r);
    //         fflush(stdout);
    //     }
    //     printf("\n");
    // }
    for (unsigned int i = 1; i < image->height - 1; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            float q = 255;
            float r = 255;
            if ((0 <= theta[i][j] && theta[i][j] < 22.5) || (157.5 <= theta[i][j] && theta[i][j] <= 180))  { 
                q = image->matrix[i][j + 1].r;
                r = image->matrix[i][j - 1].r; 
            } else {
                if ((22.5 <= theta[i][j] && theta[i][j] < 67.5)) {
                    q = image->matrix[i + 1][j - 1].r;
                    r = image->matrix[i - 1][j + 1].r;
                } else {
                    if ((67.5 <= theta[i][j] && theta[i][j] < 112.5)) {
                        q = image->matrix[i + 1][j].r;
                        r = image->matrix[i - 1][j].r;
                    } else {
                        if ((112.5 <= theta[i][j] && theta[i][j] < 157.5)) {
                            q = image->matrix[i - 1][j - 1].r;
                            r = image->matrix[i + 1][j + 1].r;
                        }
                    }
                }
            }
            Pixel newPixel;
            newPixel.a = image->matrix[i][j].a;
            if (image->matrix[i][j].r >= q && image->matrix[i][j].r >= r) {
                newPixel.r =  newPixel.g = newPixel.b = image->matrix[i][j].r;
            } else {
                newPixel.r =  newPixel.g = newPixel.b = 0;
            }
            newImage->matrix[i][j] = newPixel;
        }
    }
}
