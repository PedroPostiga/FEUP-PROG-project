#include "Image.hpp"

namespace prog {
    Image::Image(int w, int h, const Color &fill) {
        this->w = w;
        this->h = h;
        pixel_matrix = std::vector<std::vector<Color>>(h, std::vector<Color>(w, fill));
    }

    // Default constructor that creates an image with w(width) and h(height) white by default

    Image::~Image() {
    }

    int Image::width() const {
        return w;
    }

    int Image::height() const {
        return h;
    }

    // get immutable values for the variables w and h

    Color &Image::at(int x, int y) {
        return pixel_matrix[y][x];
    }

    // get mutable reference to a color object corresponding to pixel (x, y)

    const Color &Image::at(int x, int y) const {
        return pixel_matrix[y][x];
    }

    // get immutable reference to a color object corresponding to pixel (x, y)

}
