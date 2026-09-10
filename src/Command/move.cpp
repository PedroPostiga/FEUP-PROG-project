#include "Command/move.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        move::move(int x, int y) : Command("move"), x(x), y(y) {} //Constructor

        move::~move() {} //Destructor

        Image *move::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            // Iterate over all pixels from the (w - 1, h - 1) until (0, 0)
            for (int y_linha = h - 1; y_linha >= 0; y_linha--) {
                for (int x_linha = w - 1; x_linha >= 0; x_linha--) {
                    Color& c = img->at(x_linha, y_linha); // Get the color of the pixel where will it be moved to
                    // Check if the pixel will get a color
                    if (x_linha - x >= 0 && y_linha - y >= 0) {
                        Color& d = img->at(x_linha - x, y_linha - y); // Get the pixel that will be moved
                        c.red() = d.red(); c.green() = d.green(); c.blue() = d.blue(); // Put the pixel in the new position
                    }
                    // Fill with the fill color (white) all the pixels that have no color
                    else {
                        c.red() = 255; c.green() = 255; c.blue() = 255;
                    }
                }
            }
            return img;
        }

        // Moves all the pixels horizontally by x amount to the right and vertically by y amount below and the parts of the image that become without pixels get the fill color.

        std::string move::toString() const {
            std::ostringstream ss;
            ss << name() << "image moved:";
            return ss.str();
        }

    }

}