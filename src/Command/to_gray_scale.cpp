#include "Command/to_gray_scale.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        to_gray_scale::to_gray_scale() : Command("to_gray_scale") {} // Constructor

        to_gray_scale::~to_gray_scale() {} // Destructor

        Image *to_gray_scale::apply(Image *img){
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            // Iterate over all pixels
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    Color& c = img->at(x, y); // Get the color of the pixel
                    // Replace the color to gray scale (v)
                    c.red() = (c.red() + c.green() + c.blue()) / 3;
                    c.green() = c.red();
                    c.blue() = c.red();
                }
            }
            return img;
        }

        // Transforms each pixel (r, g, b) to gray scale applying (v, v, v) where v = (r + g + b) / 3

        std::string to_gray_scale::toString() const {
            std::ostringstream ss;
            ss << name() << "image to gray scale:";
            return ss.str();
        }

    }

}