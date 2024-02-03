//
// Created by eee on 27/01/2024.
//

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"
#include "interval.h"

// Alias for vector class
using color = vec3;

    /* Write the translated [0,255] value of each color component.
       Takes a value in range 0-1.
    */
void write_color(std::ofstream &file, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    const auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    static const interval intensity(0.000, 0.999);
    file << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif
