#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;
const std::string FILE_OUTPUT = "../image.ppm";


int main() {
    std::ofstream file_stream; // Open the file and reset its contents
    file_stream.open(FILE_OUTPUT, std::ios::out | std::ios::trunc);

	file_stream << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";
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
