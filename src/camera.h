//
// Created by eee on 03/02/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include <iostream>

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class camera {
public:
    double aspect_ratio = 1.0; //init to random value before actually changing by user
    int    image_width  = 2;

    camera() = default; // we use initialize in code so not needed

    void render(const hittable& world) {
        initialize();

        file_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n"; //Magic bits for ppm
        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - center;
                ray r(center, ray_direction);

                color pixel_color = ray_color(r, world);
                write_color(file_stream, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
        file_stream.close();
    }

private:
    int    image_height;        // Rendered image height
    point3 center;              // Camera center
    point3 pixel00_loc;         // Location of pixel 0, 0
    vec3   pixel_delta_u;       // Offset to pixel to the right
    vec3   pixel_delta_v;       // Offset to pixel below
    std::ofstream file_stream;  // Output file to write to

    void initialize() {
        file_stream.open(FILE_OUTPUT, std::ios::out | std::ios::trunc);

        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world) const{
        hit_record hitrec;
        if(world.hit(r, interval(0, infinity), hitrec)) {
            return 0.5 * (hitrec.normal + color(1, 1, 1));
        }
        const vec3 unit_direction = unit_vector(r.direction());
        const auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(0.71, 0.49, 0.27) + a*color(0.35, 0.85, 1.0); // linear interp
    }
};

#endif //CAMERA_H
