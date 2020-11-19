#ifndef __CONTRAST_FILTER_H_
#define __CONTRAST_FILTER_H_

#include "filter.h"

class ConstrastFilter : public Filter {
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

#endif /* __CONTRAST_FILTER_H_ */
