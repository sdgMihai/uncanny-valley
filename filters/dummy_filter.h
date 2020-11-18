#ifndef __DUMMY_FILTER_H_
#define __DUMMY_FILTER_H_

#include "filter.h"

class DummyFilter : public Filter {
    public:
        /**
         * just a dummy filter - here for fun :))
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override {
            for (unsigned int i = 1; i < image->height - 1; ++i) {
                for (unsigned int j = 1; j < image->width - 1; ++j) {
                    newImage->matrix[i][j] = image->matrix[i][j];
                }
            }
        }
};

#endif /* __DUMMY_FILTER_H_ */
