#include "Command/crop.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        crop::crop(int x, int y, int w, int h) : Command("crop"), x(x), y(y), w(w), h(h) {} // Constructor

        crop::~crop() {} // Destructor

        Image *crop::apply(Image *img) {
            Image *final_img = new Image(w, h); // New image with given dimensions
            // Iterate over the new image
            for (int y_linha = 0; y_linha < h; y_linha++) {
                for (int x_linha = 0; x_linha < w; x_linha++) {
                    Color& c = img->at(x_linha + x, y_linha + y); // Get the color of original image
                    Color& final_img_c = final_img->at(x_linha, y_linha); // Get the color of new image
                    // Put the color from original pixels in the new image
                    final_img_c.red() = c.red();
                    final_img_c.green() = c.green();
                    final_img_c.blue() = c.blue();
                }
            }
            delete img;
            return final_img;
        }

        // Crop the image, reducing it to all pixels contained in the rectangle defined by top-left corner (x, y), width w, and height h

        std::string crop::toString() const {
            std::ostringstream ss;
            ss << name() << "image cropped:";
            return ss.str();
        }

    }

}