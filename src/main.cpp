#include <iostream>
#include <fstream>

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
            auto r = double(i) / (IMAGE_WIDTH - 1);
            auto g = double(j) / (IMAGE_HEIGHT - 1);
            auto b = 0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            file_stream << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\rCompleted.               \n";
}
