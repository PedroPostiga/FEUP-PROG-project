#include "Command/invert.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        invert::invert() : Command("invert") {} // Constructor

        invert::~invert() {} // Destructor

        Image *invert::apply(Image *img) {
            int w = img->width(); // Get image height
            int h = img->height(); // Get image height
            // Iterate over all pixels
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    Color& c = img->at(x, y); // Get the color of the pixel
                    // Invert color
                    c.red()   = 255 - c.red();
                    c.green() = 255 - c.green();
                    c.blue()  = 255 - c.blue();
                }
            }
            return img;
        }

        // invert the color of each pixel (r, g, b) applying (255 - r, 255 - g, 255 - b)

        std::string invert::toString() const {
            std::ostringstream ss;
            ss << name() << "image inverted:";
            return ss.str();
        }

    }

}