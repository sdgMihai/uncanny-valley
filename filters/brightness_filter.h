#ifndef __BRIGHTNESS_FILTER_H_
#define __BRIGHTNESS_FILTER_H_

#include "filter.h"

class BrightnessFilter : public Filter {
    private:
        float brightness;

    public:
        /**
         * constructor
         * @param brightness
         */
        BrightnessFilter(float brightness) {
            this->brightness = brightness;
        }

        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override {
            
        }
};

#endif /* __BRIGHTNESS_FILTER_H_ */
