#include "Command/slide.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        slide::slide(int x, int y) : Command("slide"), x(x), y(y) {} // Constructor

        slide::~slide() {} // Destructor

        Image *slide::apply(Image *img) {
            int w = img->width(); // Get the image width
            int h = img->height(); // Get the image height
            Image *tmp = new Image(*img); // Create new image equal to original image
            // Iterate over all pixels from the (w - 1, h - 1) until (0, 0)
            for (int y_linha = h - 1; y_linha >= 0; y_linha--) {
                for (int x_linha = w - 1; x_linha >= 0; x_linha--) {
                    Color& c = img->at(x_linha, y_linha); // Get the color of the pixel where will it be moved to
                    // Check if the pixel will get a color
                    if (x_linha - x >= 0 && y_linha - y >= 0) {
                        Color& d = img->at(x_linha - x, y_linha - y); // Get the color of the pixel that will be moved
                        c.red() = d.red(); c.green() = d.green(); c.blue() = d.blue(); // Put the pixel in the new position
                    }
                    // In case of pixel will not get a color
                    else {
                        Color& d = tmp->at((w - x + x_linha) % w, (h - y + y_linha) % h); // Get the pixel color of next available position
                        c.red() = d.red(); c.green() = d.green(); c.blue() = d.blue(); // Put the color of pixels that "fall outside" in the right position
                    }
                }
            }
            delete tmp;
            return img;
        }

        // Similar to move, but instead of discarding the pixels, they “warp” to the next available position

        std::string slide::toString() const {
            std::ostringstream ss;
            ss << name() << "image slided:";
            return ss.str();
        }

    }

}