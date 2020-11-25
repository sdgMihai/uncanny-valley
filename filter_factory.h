#ifndef __FILTER_FACTORY_H_
#define __FILTER_FACTORY_H_

#include <string>
#include "filters/filter.h"
#include "utils.h"

class FilterFactory {
    public:
        /**
         * creeaza un obiect-filtru
         * @param filterName numele filtrului
         * @param brightness
         * @return referinta catre obiectul-filtru creat
         */
        static Filter* filterCreate(std::string &filterName, double param = 0.0) {
            auto it = filters.find(filterName);

            if (it == filters.end()) {
                return new DummyFilter();
            }

            switch (it->second) {
                case FILTER::SHARPEN : return new SharpenFilter();
                case FILTER::EMBOSS : return new EmbossFilter();
                case FILTER::BLACK_WHITE : return new BlackWhiteFilter();
                case FILTER::BRIGHTNESS : return new BrightnessFilter(param);
                case FILTER::CANNY_EDGE_DETECTION : return new CannyEdgeDetectionFilter();
                case FILTER::CONTRAST : return new ConstrastFilter();
                case FILTER::DOUBLE_TRESHOLD : return new DoubleTresholdFilter();
                case FILTER::EDGE_TRACKING : return new EdgeTrackingFilter();
                case FILTER::GAUSSIAN_BLUR : return new GaussianBlurFilter();
                case FILTER::NON_MAXIMUM_SUPRESSION : return new NonMaximumSupressionFilter();
                case FILTER::SEPIA : return new SepiaFilter();
            }

            return new DummyFilter();
        }
};

#endif /* __FILTER_FACTORY_H_ */
