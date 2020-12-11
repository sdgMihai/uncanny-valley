#ifndef __FILTER_FACTORY_H_
#define __FILTER_FACTORY_H_

#include <string>
#include "filter.h"
#include "utils.h"

class FilterFactory {
    public:
        /**
         * creeaza un obiect-filtru
         * @param filterName numele filtrului
         * @param brightness
         * @return referinta catre obiectul-filtru creat
         */
        static Filter* filterCreate(std::string &filterName, double param = 0.0,
                                    float **theta = nullptr, unsigned int thetaHeight = 0, 
                                    unsigned int thetaWidth = 0, void *varargs = nullptr) {
            auto it = filters.find(filterName);

            if (it == filters.end()) {
                return new DummyFilter();
            }

            switch (it->second) {
                case FILTER::SHARPEN : return new SharpenFilter(varargs);
                case FILTER::EMBOSS : return new EmbossFilter(varargs);
                case FILTER::BLACK_WHITE : return new BlackWhiteFilter(varargs);
                case FILTER::BRIGHTNESS : return new BrightnessFilter(param, varargs);
                case FILTER::CANNY_EDGE_DETECTION : return new CannyEdgeDetectionFilter(varargs);
                case FILTER::CONTRAST : return new ConstrastFilter(param, varargs);
                case FILTER::DOUBLE_TRESHOLD : return new DoubleTresholdFilter(varargs);
                case FILTER::EDGE_TRACKING : return new EdgeTrackingFilter(varargs);
                case FILTER::GAUSSIAN_BLUR : return new GaussianBlurFilter(varargs);
                case FILTER::NON_MAXIMUM_SUPPRESSION : return new NonMaximumSuppressionFilter(theta, thetaHeight, thetaWidth, varargs);
                case FILTER::GRADIENT : return new GradientFilter(varargs);
                case FILTER::SEPIA : return new SepiaFilter(varargs);
            }

            return new DummyFilter(varargs);
        }
};

#endif /* __FILTER_FACTORY_H_ */
