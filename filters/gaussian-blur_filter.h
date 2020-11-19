#ifndef __GAUSSIAN_BLUR_FILTER_H_
#define __GAUSSIAN_BLUR_FILTER_H_

#include "filter.h"

class GaussianBlurFilter : public Filter {
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

#endif /* __GAUSSIAN_BLUR_FILTER_H_ */
