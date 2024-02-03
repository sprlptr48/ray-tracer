//
// Created by eee on 02/02/2024.
//

#ifndef RTWEEKEND_H
#define RTWEEKEND_H
//General Definitions and tools for use

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932384626433832795028841971693;

const std::string FILE_OUTPUT = "../image.ppm";

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#endif //RTWEEKEND_H
