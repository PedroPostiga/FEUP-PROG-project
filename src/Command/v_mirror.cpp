#include "Command/v_mirror.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        v_mirror::v_mirror() : Command("v_mirror") {} // Constructor

        v_mirror::~v_mirror() {} // Destructor

        Image *v_mirror::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            // Iterate over the upper half of the image
            for (int y = 0; y < h / 2; y++) {
                for (int x = 0; x < w ; x++) {
                    Color& c = img->at(x, y); // Get the color of the pixel from upper half
                    Color& d = img->at(x, h - y - 1); // Get the color of the pixel from lower half
                    // Copy the color from upper half
                    rgb_value r = c.red();
                    rgb_value g = c.green();
                    rgb_value b = c.blue();
                    c.red() = d.red(); c.green() = d.green(); c.blue() = d.blue(); // Put the color of the pixel from lower half to the pixel from upper half
                    d.red() = r; d.green() = g; d.blue() = b; // Put the color of the pixel from upper half to the pixel from lower half
                }
            }
            return img;
        }

        // Mirror vertically the image

        std::string v_mirror::toString() const {
            std::ostringstream ss;
            ss << name() << "image mirrored vertically:";
            return ss.str();
        }

    }

}