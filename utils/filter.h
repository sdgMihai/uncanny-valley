#ifndef __FILTER_H_
#define __FILTER_H_

#include "image.h"

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
    private:
        // intre -128 si 128
        float contrast;

    public:
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
    private:
        const float thresholdHigh = 0.1;
        const float thresholdLow = 0.05;

    public:
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
        float **theta; /* place to save theta calculation */
        unsigned int thetaHeight;
        unsigned int thetaWidth;
    
    public:
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;

        virtual ~GradientFilter() {
            for (unsigned int i = 0; i < this->thetaHeight; ++i) {
                delete[] this->theta[i];
            }
            delete[] this->theta;
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

class NonMaximumSuppressionFilter : public Filter {
    private:
        float **theta;
        unsigned int thetaHeight;
        unsigned int thetaWidth;

    public:
        NonMaximumSuppressionFilter(float **theta, unsigned int thetaHeight, unsigned int thetaWidth) {
            this->thetaWidth = thetaWidth;
            this->thetaHeight = thetaHeight;
            this->theta = new float *[thetaHeight];

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

        virtual ~NonMaximumSuppressionFilter() {
            if (this->theta) {
                for (unsigned int i = 0; i < this->thetaHeight; ++i) {
                    delete[] this->theta[i];
                }
                delete[] this->theta;
            }
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
        virtual void applyFilter(Image *image, Image *newImage) override;
};

#endif /* __FILTER_H_ */
