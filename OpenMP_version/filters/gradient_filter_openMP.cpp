#include "../../utils/filter.h"
#include <cmath>
#include <cstdio>
#include <omp.h>

static const float Gx[3][3] = {{-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}};

static const float Gy[3][3] = {{1, 2, 1},
                                {0, 0, 0},
                                {-1, -2, -1}};


/* Cel mai mare din filtre, se aplica pasii de mai jos pe rand */
void GradientFilter::applyFilter(Image *image, Image *newImage) {
    float **Ix, **Iy;
    float gMax = -MAXFLOAT;

    Ix = new float *[image->height];
    Iy = new float *[image->height];
    this->theta = new float *[image->height];
    float **theta = this->theta;
    
    this->thetaHeight = image->height;
    this->thetaWidth = image->width;

    #pragma omp parallel for
        for (unsigned int i = 0; i < image->height; ++i) {
            Ix[i] = new float[image->width]();
            Iy[i] = new float[image->width]();
            theta[i] = new float [image->width]();
        }

    /* 1. Se aplica kernelul Gx pe imagine si se obtine Ix */
    #pragma omp parallel for
        for (unsigned int i = 1; i < image->height - 1; ++i) {
            for (unsigned int j = 1; j < image->width - 1; ++j) {
                float gray = 0;

                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        gray += static_cast<float>(image->matrix[i + ki][j + kj].r) * Gx[ki + 1][kj + 1];
                    }
                }
                Ix[i][j] = gray;
            }
        }

    /* 2. Se aplica kernelul Gy pe imagine si se obtine Iy */
    #pragma omp parallel for
        for (unsigned int i = 1; i < image->height - 1; ++i) {
            for (unsigned int j = 1; j < image->width - 1; ++j) {
                float gray = 0;

                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        gray += static_cast<float>(image->matrix[i + ki][j + kj].r) * Gy[ki + 1][kj + 1];
                    }
                }
                Iy[i][j] = gray;
            }
        }

    /**
     * 3. Se calculeaza G = sqrt(Gx**2 + Gy**2) pe fiecare element,
     * se foloseste Ix ca depozit.
     * Se calculeaza theta = arctangenta(Iy, Ix) pe fiecare element
     */
    #pragma omp parallel for reduction(max:gMax)
        for (unsigned int i = 1; i < image->height - 1; ++i) {
            for (unsigned int j = 1; j < image->width - 1; ++j) {
                float gray;
                gray = sqrt(Ix[i][j] * Ix[i][j] + Iy[i][j] * Iy[i][j]);
                if (gray > gMax) {
                    gMax = gray;
                }
                Ix[i][j] = gray;
                theta[i][j] =  atan2(Iy[i][j], Ix[i][j]) * 180 / M_PI;
                if (theta[i][j] < 0) {
                    theta[i][j] += 180;
                }
            }
        }

    /* 4. Se calculeaza G = G / G.max() * 255 */
    #pragma omp parallel for
        for (unsigned int i = 1; i < image->height - 1; ++i) {
            for (unsigned int j = 1; j < image->width - 1; ++j) {
                float gray = Ix[i][j];
                gray = (gray / gMax) * 255;
                gray = (gray < 0) ? 0 : gray;
                gray = (gray > 255) ? 255 : gray;
                newImage->matrix[i][j] = Pixel(gray, gray, gray, image->matrix[i][j].a);
            }
        }

    #pragma omp parallel for
        for (unsigned int i = 0; i < image->height; ++i) {
            delete[] Ix[i];
            delete[] Iy[i];
        }
    delete[] Ix;
    delete[] Iy;
}