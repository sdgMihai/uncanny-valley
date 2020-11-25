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
        virtual void applyFilter(Image *image, Image *newImage) = 0;

        virtual ~Filter() {}
};

class BlackWhiteFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class CannyEdgeDetectionFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class ConstrastFilter : public Filter {
    public:
        // intre -128 si 128
        float contrast;

        /**
         * constructor
         * @param contrast
         */
        ConstrastFilter(float contrast) {
            this->contrast = contrast;
        }

        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class DoubleTresholdFilter : public Filter {
    public:
        const float thresholdHigh = 0.1;
        const float thresholdLow = 0.05;
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class GradientFilter : public Filter {
    public:
        float **theta; // place to save theta calculation
        unsigned int thetaHeight;
        unsigned int thetaWidth;

        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;

        virtual ~GradientFilter() {
            for (unsigned int i = 0; i < thetaHeight; ++i) {
                delete theta[i];
            }
            delete theta;
        }
};

class DummyFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class EdgeTrackingFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class EmbossFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class GaussianBlurFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class NonMaximumSupressionFilter : public Filter {
    public:
        float **theta;
        unsigned int thetaHeight;
        unsigned int thetaWidth;

        NonMaximumSupressionFilter() {

        }

        NonMaximumSupressionFilter(float **theta, unsigned int thetaHeight, unsigned int thetaWidth) {
            this->thetaWidth = thetaWidth;
            this->thetaHeight = thetaHeight;
            this->theta =new float *[thetaHeight];

            for (unsigned int i = 0; i < thetaHeight; ++i) {
                this->theta[i] = new float[thetaWidth];
                for (unsigned int j = 0; j < thetaWidth; ++j) {
                    this->theta[i][j] = theta[i][j];
                }
            }
        }

        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;

        virtual ~NonMaximumSupressionFilter() {
            for (unsigned int i = 0; i < thetaHeight; ++i) {
                delete theta[i];
            }
            delete theta;
        }
};

class SepiaFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class SharpenFilter : public Filter {
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class BrightnessFilter : public Filter {
    public:
        float brightness;

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
        virtual void applyFilter(Image *image, Image *newImage) override;
};

#endif /* __FILTER_H_ */
