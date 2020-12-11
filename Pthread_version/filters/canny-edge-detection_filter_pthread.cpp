#include "../../utils/filter.h"
#include "../helpers_pthread.h"

/**
 * TODO:
 *  Acest filtru foloseste mai multe filtre aplicate succesiv:
 *   black&white, gaussian blur, gradient, non-maximum supression, double threshold, edge tracking
 */
static float **auxTheta;

void CannyEdgeDetectionFilter::applyFilter(Image *image, Image *newImage) {
    thread_specific_data_t *t_data = (thread_specific_data_t *) this->filter_additional_data;

    u_int64_t slice = (image->height - 2) / NUM_THREADS;
    u_int64_t start = thread_max(1, t_data->thread_id * slice);
    u_int64_t stop  = (t_data->thread_id + 1) * slice;
    if (t_data->thread_id + 1 == NUM_THREADS) {
        stop = thread_max((t_data->thread_id + 1) * slice, (image->height - 1));
    }

    BlackWhiteFilter step1(t_data);
    step1.applyFilter(image, newImage);
    pthread_barrier_wait(t_data->barrier);

    GaussianBlurFilter step2(t_data);
    step2.applyFilter(newImage, image);
    pthread_barrier_wait(t_data->barrier);

    GradientFilter step3(t_data);
    step3.applyFilter(image, newImage);
    if (t_data->thread_id == 0) {
        auxTheta = step3.theta;
    }
    pthread_barrier_wait(t_data->barrier);

    NonMaximumSuppressionFilter step4(auxTheta, step3.thetaHeight, step3.thetaWidth, t_data);
    step4.applyFilter(newImage, image);
    pthread_barrier_wait(t_data->barrier);

    DoubleTresholdFilter step5(t_data);
    step5.applyFilter(image, newImage);
    pthread_barrier_wait(t_data->barrier);

    EdgeTrackingFilter step6(t_data);
    step6.applyFilter(newImage, image);
    pthread_barrier_wait(t_data->barrier);

    // Clean noise
    for (unsigned int i = start; i < stop; ++i) {
        Pixel *swp = image->matrix[i];
        image->matrix[i] = newImage->matrix[i];
        newImage->matrix[i] = swp;
        for (unsigned int j = 1; j < image->width - 1; ++j) {
            if (newImage->matrix[i][j].r < 100) {
                newImage->matrix[i][j] = Pixel(0, 0, 0, newImage->matrix[i][j].a);
            }
        }
    }
}
