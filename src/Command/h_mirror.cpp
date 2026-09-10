#include "Command/h_mirror.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        h_mirror::h_mirror() : Command("h_mirror") {} // Constructor

        h_mirror::~h_mirror() {} // Destructor

        Image *h_mirror::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            // Iterate over the left half of the image
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w / 2; x++) {
                    Color& c = img->at(x, y); // Get the color of the pixel from left half
                    Color& d = img->at(w - 1 - x, y); // Get the color of the pixel from right half
                    // Copy the color from left half
                    rgb_value r = c.red();
                    rgb_value g = c.green();
                    rgb_value b = c.blue();
                    c.red() = d.red(); c.green() = d.green(); c.blue() = d.blue(); // Put the color of the pixel from right half to the pixel from left half
                    d.red() = r; d.green() = g; d.blue() = b; // Put the color of the pixel from left half to the pixel from right half
                }
            }
            return img;
        }

        // Mirror horizontally the image

        std::string h_mirror::toString() const {
            std::ostringstream ss;
            ss << name() << "image mirrored horizontally:";
            return ss.str();
        }

    }

}