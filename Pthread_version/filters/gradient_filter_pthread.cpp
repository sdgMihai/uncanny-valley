#include "../../utils/filter.h"
#include "../helpers_pthread.h"
#include <cmath>
#include <cstdio>

static const float Gx[3][3] = {{-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}};

static const float Gy[3][3] = {{1, 2, 1},
                                {0, 0, 0},
                                {-1, -2, -1}};

static float gMax = -3.40282347e+38F;
static float **Ix, **Iy, **auxTheta;

// Cel mai mare din filtre, se aplica pasii de mai jos pe rand
void GradientFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    if (t_data->thread_id == 0)
    {
        Ix = new float *[image->height];
        Iy = new float *[image->height];
        auxTheta = new float *[image->height];
        this->thetaHeight = image->height;
        this->thetaWidth = image->width;

        for (unsigned int i = 0; i < image->height; ++i) {
            Ix[i] = new float[image->width]();
            Iy[i] = new float[image->width]();
            auxTheta[i] = new float [image->width]();
        }
    }
    this->thetaHeight = image->height;
    this->thetaWidth = image->width;
    pthread_barrier_wait(t_data->barrier);
    this->theta = auxTheta;

    // 1. Se aplica kernelul Gx pe imagine si se obtine Ix
    for (unsigned int i = start; i < stop; ++i) {
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

    // 2. Se aplica kernelul Gy pe imagine si se obtine Iy
    for (unsigned int i = start; i < stop; ++i) {
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

    float threadgMax = -3.40282347e+38F;
    // 3. Se calculeaza G = sqrt(Gx**2 + Gy**2) pe fiecare element, se foloseste Ix ca depozit
    // Se calculeaza theta = arctangenta(Iy, Ix) pe fiecare element
    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            float gray;
            gray = sqrt(Ix[i][j] * Ix[i][j] + Iy[i][j] * Iy[i][j]);
		    if (threadgMax < gray) {
                threadgMax = gray;
            }
            this->theta[i][j] =  atan2(Iy[i][j], Ix[i][j]) * 180 / M_PI;
            Ix[i][j] = gray;
            if (this->theta[i][j] < 0) {
                this->theta[i][j] += 180;
            }
        }
    }

    pthread_mutex_lock(t_data->mutex);
    gMax = (gMax < threadgMax) ? threadgMax : gMax;
    pthread_mutex_unlock(t_data->mutex);
    pthread_barrier_wait(t_data->barrier);

    // 4. Se calculeaza G = G / G.max() * 255
    for (unsigned int i = start; i < stop; ++i) {
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            float gray = Ix[i][j];
            gray = (gray / gMax) * 255;
            gray = (gray < 0) ? 0 : gray;
            gray = (gray > 255) ? 255 : gray;
            newImage->matrix[i][j] = Pixel(gray, gray, gray, image->matrix[i][j].a);
        }
    }

    if (t_data->thread_id == 0)
    {
        for (unsigned int i = 0; i < image->height; ++i) {
            delete[] Ix[i];
            delete[] Iy[i];
        }
        delete[] Ix;
        delete[] Iy;
    } else {
        this->theta = NULL;
    }
}