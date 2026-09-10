#include "Command/resize.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        resize::resize(int x, int y, int w, int h) : Command("resize"), x(x), y(y), w(w), h(h) {} // Constructor

        resize::~resize() {} // Destructor

        Image *resize::apply(Image *img) {
            int old_img_w = img->width(); // Get image width
            int old_img_h = img->height(); // Get image height
            Image *final_img = new Image(w, h); // Create a new image with (w, h) size
            // Iterate over the rectangle that starts in (x, y) and ends in (x + w, y + h)
            for (int y_linha = y; y_linha < h; y_linha++) {
                for (int x_linha = x; x_linha < w; x_linha++) {
                    if (x_linha < old_img_w && y_linha < old_img_h) {
                        Color& c = img->at(x_linha, y_linha); // Get the color of the pixel
                        Color& final_img_c = final_img->at(x_linha - x, y_linha - y); // Get the color of the new image pixel
                        // Put the color from original pixels in the new image
                        final_img_c.red() = c.red(); // Put the amount of red from the first image in the new one
                        final_img_c.green() = c.green(); // Put the amount of green from the first image in the new one
                        final_img_c.blue() = c.blue(); // Put the amount of blue from the first image in the new one
                    }
                }
            }
            delete img;
            return final_img;
        }

        // Reduce the image to all pixels contained in the rectangle defined by top-left corner (x, y), width w, and height h. Pixels that are not within the current image are filled with the image’s fill color

        std::string resize::toString() const {
            std::ostringstream ss;
            ss << name() << "image resized:";
            return ss.str();
        }

    }

}