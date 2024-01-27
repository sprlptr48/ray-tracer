//
// Created by eee on 27/01/2024.
//

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// Alias for vector class
using color = vec3;

    /* Write the translated [0,255] value of each color component.
       Takes a value in range 0-1.
    */
void write_color(std::ofstream &file, color pixel_color) {
    file << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif
