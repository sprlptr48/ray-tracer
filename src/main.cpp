#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

constexpr auto ASPECT_RATIO = 16.0 / 9.0;
constexpr int IMAGE_WIDTH = 400;
// Calculate the image height. //No check for if lower than 1
constexpr int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

constexpr std::string FILE_OUTPUT = "../image.ppm";

int main() {
    // Open the file and reset its contents
    std::ofstream file_stream;
    file_stream.open(FILE_OUTPUT, std::ios::out | std::ios::trunc);
    //Camera values
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);
    constexpr auto viewport_height = 2.0;
    constexpr auto viewport_width = viewport_height * (static_cast<double>(IMAGE_WIDTH)/IMAGE_HEIGHT);

    auto viewport_u = vec3(viewport_width, 0, 0); //GLSL uv Coords
    auto viewport_v = vec3(0, -viewport_height, 0); //GLSL uv Coords

    auto pixel_delta_u = viewport_u / IMAGE_WIDTH;
    auto pixel_delta_v = viewport_v / IMAGE_HEIGHT;

	file_stream << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n"; //Magic bits for ppm
    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            auto pixel_color = color(double(i)/(IMAGE_WIDTH-1), double(j)/(IMAGE_HEIGHT-1), 0);
            write_color(file_stream, pixel_color);
        }
    }
    std::clog << "\rCompleted.               \n";
    file_stream.close();
}

color ray_color(const ray& r) {
    return color(0, 112, 221);
}