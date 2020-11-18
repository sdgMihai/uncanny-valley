#ifndef __FILTER_FACTORY_H_
#define __FILTER_FACTORY_H_

#include <string>
#include "./filters/filter.h"
#include "./filters/emboss_filter.h"
#include "./filters/sharpen_filter.h"
#include "./filters/dummy_filter.h"
#include "utils.h"

class FilterFactory {
    public:
        static Filter* filterCreate(std::string &filterName) {
            auto it = filters.find(filterName);

            if (it == filters.end()) {
                return new DummyFilter();
            }

            /**
             * TODO: va trebui cumva sa ascundem acele valori (0, 1) cu niste macro-uri
             * sau orice alta solutie :)) sa fie mai elegant
             */
            switch (it->second) {
                case 0: return new SharpenFilter();
                case 1: return new EmbossFilter();
            }

            return new DummyFilter();
        }
};

#endif /* __FILTER_FACTORY_H_ */
