#ifndef __FILTER_H_
#define __FILTER_H_

#include "../image.h"

class Filter {
    public:
        /**
         * aplica un filtru pe imagine
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *images, Image *newImage) = 0;

        virtual ~Filter() {}
};

#endif /* __FILTER_H_ */
