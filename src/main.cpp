#include <iostream>
#include <fstream>

#include "rtweekend.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

constexpr auto ASPECT_RATIO = 16.0 / 9.0;
constexpr int IMAGE_WIDTH = 400;
// Calculate the image height. //No check for if lower than 1
constexpr int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

const std::string FILE_OUTPUT = "../image.ppm";

color ray_color(const ray& r, const hittable& world) {
    hit_record hitrec;
    if(world.hit(r, 0, infinity, hitrec)) {
        return 0.5 * (hitrec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.9, 0.5, 0.9); // linear interp
}

int main() {
    // Open the file and reset its contents
    std::ofstream file_stream;
    file_stream.open(FILE_OUTPUT, std::ios::out | std::ios::trunc);
    //Camera values
    constexpr auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);
    constexpr auto viewport_height = 2.0;
    constexpr auto viewport_width = viewport_height * (static_cast<double>(IMAGE_WIDTH)/IMAGE_HEIGHT);

    auto viewport_u = vec3(viewport_width, 0, 0); //GLSL uv Total size width
    auto viewport_v = vec3(0, -viewport_height, 0); //GLSL uv Total size height

    auto pixel_delta_u = viewport_u / IMAGE_WIDTH; // GLSL current UV width
    auto pixel_delta_v = viewport_v / IMAGE_HEIGHT; // GLSL current UV height

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //Create a world with two spheres for now
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
    world.add(make_shared<sphere>(point3(-15,5.5,-15), 4));
	file_stream << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n"; //Magic bits for ppm
    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(file_stream, pixel_color);
        }
    }
    std::clog << "\rCompleted.               \n";
    file_stream.close();
}
