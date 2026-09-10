#include "Command/fill.hpp"
#include "Image.hpp"
#include "Color.hpp"
#include <sstream>

namespace prog {

    namespace command {

        fill::fill(int x, int y, int w, int h, Color &fill_) : Command("fill"), x(x), y(y), w(w), h(h), fill_(fill_) {} // Constructor

        fill::~fill() {} // Destructor

        Image *fill::apply(Image *img) {
            // Iterate over the rectangle that starts in (x, y) and ends in (x + w, y + h)
            for (int y_linha = y; y_linha < y + h; y_linha++) {
                for (int x_linha = x; x_linha < x + w; x_linha++) {
                    Color& c = img->at(x_linha, y_linha); // Get the color of the pixel
                    // Replace the original color with fill color
                    c.red()   = fill_.red();
                    c.green() = fill_.green();
                    c.blue()  = fill_.blue();
                }
            }
            return img;
        }

        // Fill the rectangle that starts in (x, y) and ends in (x + w, y + h) with color "fill"

        std::string fill::toString() const {
            std::ostringstream ss;
            ss << name() << " x: " << x << " y:" << y << " w:" << w << " h:" << h << " fill:" << fill_;
            return ss.str();
        }

    }

}