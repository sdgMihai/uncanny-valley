#ifndef __FILTER_H_
#define __FILTER_H_

#include "image.h"
#include "utils.h"
#include "../MPI_version/mpi_data.h"

class Filter {
    protected:
        void *filter_additional_data;

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
        BlackWhiteFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }

        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;
};

class CannyEdgeDetectionFilter : public Filter {
    private:
        int rank;
        int numtasks;
        int chunk;
    public:
        CannyEdgeDetectionFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
            if (this->filter_additional_data != nullptr) {
                rank = ((my_t_data *) filter_additional_data)->rank;
                numtasks = ((my_t_data *) filter_additional_data)->numtasks;
                chunk = ((my_t_data *) filter_additional_data)->chunk;
            }
        }
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
        ConstrastFilter(float contrast, void *filter_additional_data = nullptr) {
            this->contrast = contrast;
            this->filter_additional_data = filter_additional_data;
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
        const float thresholdHigh = 0.06;
        const float thresholdLow = 0.05;

    public:
        DoubleTresholdFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        GradientFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;

        virtual ~GradientFilter() {
            if (this->theta) {
                for (unsigned int i = 0; i < this->thetaHeight; ++i) {
                    delete[] this->theta[i];
                }
                delete[] this->theta;
            }
        }
};

class DummyFilter : public Filter {
    public:
        DummyFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        EdgeTrackingFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        EmbossFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        GaussianBlurFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        NonMaximumSuppressionFilter(float **theta, unsigned int thetaHeight,
            unsigned int thetaWidth, void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
            this->thetaWidth = thetaWidth;
            this->thetaHeight = thetaHeight;
            this->theta = theta;
        }

        /**
         * @param image referinta catre imagine
         * @param newImage referinta catre obiectul tip Image
         *          care va contine imaginea rezultata in urma
         *          aplicarii filtrului.
         */
        virtual void applyFilter(Image *image, Image *newImage) override;

        virtual ~NonMaximumSuppressionFilter() {
            
        }
};

class SepiaFilter : public Filter {
    public:
        SepiaFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        SharpenFilter(void *filter_additional_data = nullptr) {
            this->filter_additional_data = filter_additional_data;
        }
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
        BrightnessFilter(float brightness, void *filter_additional_data = nullptr) {
            this->brightness = brightness;
            this->filter_additional_data = filter_additional_data;
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
