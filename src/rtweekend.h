//
// Created by eee on 02/02/2024.
//

#ifndef RTWEEKEND_H
#define RTWEEKEND_H
//General Definitions and tools for use

#include <cmath>
#include <random>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932384626433832795028841971693;

const std::string FILE_OUTPUT = "../image.ppm";

inline double degrees_to_radians(const double degrees) {
    return degrees * pi / 180.0;
}

// random in [0,1) range
inline double random_double() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> ranDouble(0.0, 1.0);
    return ranDouble(gen); // random in range [0, 1)
}

// Random double in [min, max) range
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#endif //RTWEEKEND_H
