#include "Command/scaleup.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        scaleup::scaleup(int x, int y) : Command("scaleup"), x(x), y(y) {} // Constructor

        scaleup::~scaleup() {} // Destructor

        Image *scaleup::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // get image height
            Image *final_img = new Image(x * w, y * h); // Create a new image with (x * w, y * h) size
            // Iterate over all pixels of original image
            for (int y_linha = 0; y_linha < h; y_linha++) {
                for (int x_linha = 0; x_linha < w; x_linha++) {
                  Color& c = img->at(x_linha, y_linha); // Get the pixel color
                  // Iterate over the rectangle with dimensions (x, y)
                  for (int i = 0; i < x; i++){
                    for (int k = 0; k < y; k++){
                    Color& final_img_c = final_img->at(x * x_linha + i, y * y_linha + k); // Get the pixel color
                    // Put the color in pixel
                    final_img_c.red() = c.red();
                    final_img_c.green() = c.green();
                    final_img_c.blue() = c.blue();
                    }
                  }
                }
            }
            delete img;
            return final_img;
        }

        // Each pixel expands horizontally by integer factor x and vertically by integer factor y

        std::string scaleup::toString() const {
            std::ostringstream ss;
            ss << name() << "image scaled up:";
            return ss.str();
        }

    }

}
