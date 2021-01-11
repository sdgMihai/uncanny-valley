#ifndef __UTILS_H_
#define __UTILS_H_

#include <string>
#include <unordered_map>

/**
 * OBS: il definim in Makefile
 */
/**
 * ASSERT folosit pentru debugging
 */
#ifdef ASSERT_ENABLE
#include <cassert>
#define ASSERT(x) assert(x);
#else
#define ASSERT(x)
#endif /* ASSERT_ENABLE */

/**
 * filtrele disponibile
 */
/**
 * id-urile filtrelor
 */
enum FILTER {
    SHARPEN = 0,
    EMBOSS,
    SEPIA,
    CONTRAST,
    BRIGHTNESS,
    BLACK_WHITE,
    GAUSSIAN_BLUR,
    NON_MAXIMUM_SUPPRESSION,
    DOUBLE_TRESHOLD,
    EDGE_TRACKING,
    GRADIENT,
    CANNY_EDGE_DETECTION
};

/**
 * asociere intre numele filtrului si id-ul acestuia
 */
const std::unordered_map<std::string, FILTER> filters = {
    {"sharpen", FILTER::SHARPEN},
    {"emboss", FILTER::EMBOSS},
    {"sepia", FILTER::SEPIA},
    {"contrast", FILTER::CONTRAST},
    {"brightness", FILTER::BRIGHTNESS},
    {"black-white", FILTER::BLACK_WHITE},
    {"gaussian-blur", FILTER::GAUSSIAN_BLUR},
    {"non-maximum-suppression", FILTER::NON_MAXIMUM_SUPPRESSION},
    {"double-threshold", FILTER::DOUBLE_TRESHOLD},
    {"edge-tracking", FILTER::EDGE_TRACKING},
    {"gradient", FILTER::GRADIENT},
    {"canny-edge-detection", FILTER::CANNY_EDGE_DETECTION}
};

#endif /* __UTILS_H_ */
