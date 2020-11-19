#ifndef __CANNY_EDGE_DETECTION_FILTER_H_
#define __CANNY_EDGE_DETECTION_FILTER_H_

#include "filter.h"

/**
 * TODO:
 *  Acest filtru foloseste mai multe filtre aplicate succesiv:
 *   black&white, gaussian blur, emboss, non-maximum supression, double threshold, edge tracking
 */

class CannyEdgeDetectionFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override {
            
        }
};

#endif /* __CANNY_EDGE_DETECTION_FILTER_H_ */
