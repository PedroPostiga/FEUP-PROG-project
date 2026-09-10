#include "Command/rotate_left.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        rotate_left::rotate_left() : Command("rotate_left") {} // Constructor

        rotate_left::~rotate_left() {} // Destructor

        Image *rotate_left::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            Image *final_img = new Image(h, w); // Create a image with (h , w) size
            // Iterate over all pixels
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    Color& c = img->at(x, y); // Get the pixel color
                    Color& final_img_c = final_img->at(y,w - x - 1); // Get the pixel color of new position (rotate 90 degrees left)
                    // Put the color of pixel at new position
                    final_img_c.red() = c.red();
                    final_img_c.green() = c.green();
                    final_img_c.blue() = c.blue();
                }
            }
            delete img;
            return final_img;
        }

        // Rotate the image left by 90 degrees

        std::string rotate_left::toString() const {
            std::ostringstream ss;
            ss << name() << "image rotated left by 90 degrees:";
            return ss.str();
        }

    }

}