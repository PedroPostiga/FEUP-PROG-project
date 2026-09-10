#include "Command/replace.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        replace::replace(Color &to_replace, Color &replaced) : Command("replace"), to_replace(to_replace), replaced(replaced){} // Constructor

        replace::~replace() {}; // Destructor

        Image *replace::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            // Iterate over all pixels
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    Color& c = img->at(x, y); // Get the color of the pixel
                    // Check if the pixel have the color to replace
                    if (c.red() == to_replace.red() && c.blue() == to_replace.blue() && c.green() == to_replace.green()) {
                        // Replace the color
                        c.red() = replaced.red();
                        c.green() = replaced.green();
                        c.blue() = replaced.blue();
                    }
                }
            }
            return img;
        }

        // Replace all pixels with color (r1, g1, b1) by color (r2, g2, b2)

        std::string replace::toString() const {
            std::ostringstream ss;
            ss << name() << "image pixel's replaced:";
            return ss.str();
        }

    }

}