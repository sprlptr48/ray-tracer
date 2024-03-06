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
#include "material.h"

class camera {
public:
    char camName = ' ';         // Camera name for debug
    double aspect_ratio = 1.0;  // init to random value before actually changing by user
    int    image_width  = 10;
    int    samples_per_pixel = 10;
    int    max_depth = 10;      // Max number of bounces

    double fov = 90;            // Vertical Field of View (View Angle)
    point3 lookfrom = point3(0, 0, -1);
    point3 lookat = point3(0, 0, 0);
    vec3 vup = vec3(0, 1, 0); // Camera relative up direction

    double defocus_angle = 0;       // Variation angle of rays through each pixel
    double focus_dist = 10;         // Distance from camera lookfrom point to plane of perfect focus

    camera() = default; // we use initialize in code so not needed

    void render(const hittable& world) {
        initialize();

        file_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n"; //Magic bits for ppm
        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - center;

                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(file_stream, pixel_color, samples_per_pixel);
            }
        }

        std::clog << "\rRendering of " << camName << " Done.  \n";
        file_stream.close();
    }

private:
    int    image_height;        // Rendered image height
    point3 center;              // Camera center
    point3 pixel00_loc;         // Location of pixel 0, 0
    vec3   pixel_delta_u;       // Offset to pixel to the right
    vec3   pixel_delta_v;       // Offset to pixel below
    vec3 u, v, w;               // Camera basis vectors
    vec3   defocus_disk_u;      // Defocus disk horizontal radius
    vec3   defocus_disk_v;      // Defocus disk vertical radius
    std::ofstream file_stream;  // Output file to write to

    void initialize() {
        file_stream.open(FILE_OUTPUT, std::ios::out | std::ios::trunc);

        // Calculate image height from width
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = lookfrom; // Camera location

        // Determine viewport dimensions.
        auto theta = degrees_to_radians(fov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h * focus_dist;
        auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height  * -v;

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - focus_dist*w - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        // Calculate the camera defocus disk basis vectors.
        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    point3 defocus_disk_sample() const {
        // Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const{
        hit_record hitrec;

        if (depth <= 0) {
            return color(0, 0, 0);
        }
        if(world.hit(r, interval(0.00125, infinity), hitrec)) {
            ray scattered;
            color attenuation;
            if (hitrec.mat->scatter(r, hitrec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, depth-1, world);
            }
            return color(0,0,0);
        }
        const vec3 unit_direction = unit_vector(r.direction());
        const auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(0.71, 0.49, 0.27) + a*color(0.35, 0.85, 1.0); // linear interp
    }



    // Get a randomly-sampled camera ray for the pixel at location i,j, originating from
    // the camera defocus disk.
    ray get_ray(int i, int j) const {
        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v); // Default center
        auto pixel_sample = pixel_center + pixel_sample_square(); // Random offset added↑ sample point

        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    // Returns a random point in the square surrounding a pixel at the origin.
    vec3 pixel_sample_square() const {
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

};

#endif //CAMERA_H
