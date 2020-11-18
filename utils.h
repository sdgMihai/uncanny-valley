#ifndef __UTILS_H_
#define __UTILS_H_

#include <string>
#include <unordered_map>

/**
 * TODO: il definim in Makefile
 */
// #define ASSERT_ENABLE

/**
 * ASSERT folosit pentru debugging
 */
#ifdef ASSERT_ENABLE
#define ASSERT(x) assert(x);
#else
#define ASSERT(x)
#endif /* ASSERT_ENABLE */

/**
 * filtrele disponibile
 */
// #define SHARPEN_FILTER "sharpen"
// #define EMBOSS_FILTER  "emboss"

const std::unordered_map<std::string, unsigned int> filters = {
    {"sharpen", 0},
    {"emboss", 1}
};

#endif /* __UTILS_H_ */
