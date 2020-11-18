#ifndef __SHARPEN_FILTER_H_
#define __SHARPEN_FILTER_H_

#include "filter.h"

class SharpenFilter : public Filter {
    public:
        /**
         * aplica filtrul SHARPEN pe imagine
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override {

        }
};

#endif /* __SHARPEN_FILTER_H_ */
