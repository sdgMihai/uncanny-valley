#include "filter.h"

/**
 * TODO:
 *  Acest filtru foloseste mai multe filtre aplicate succesiv:
 *   black&white, gaussian blur, gradient, non-maximum supression, double threshold, edge tracking
 */

void CannyEdgeDetectionFilter::applyFilter(Image *image, Image *newImage) {


    BlackWhiteFilter step1;
    step1.applyFilter(image, newImage);
    GaussianBlurFilter step2;
    step2.applyFilter(newImage, image);
    GradientFilter step3;
    step3.applyFilter(image, newImage);
    NonMaximumSuppressionFilter step4(step3.theta, step3.thetaHeight, step3.thetaWidth);
    step4.applyFilter(newImage, image);
    DoubleTresholdFilter step5;
    step5.applyFilter(image, newImage);
    EdgeTrackingFilter step6;
    step6.applyFilter(newImage, image);

    // Clean noise
    for (unsigned int i = 1; i < image->height - 1; ++i) {
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
