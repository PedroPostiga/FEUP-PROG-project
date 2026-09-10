#include "Command/add.hpp"
#include "Command/Open.hpp"

#include "Image.hpp"
#include "Color.hpp"
#include <sstream>
#include <utility>

namespace prog {

    namespace command {

        add::add(std::string filename, Color neutral, int x, int y) : Command("add"), filename(std::move(filename)), neutral(neutral), x(x), y(y) {}

        add::~add() {}

        Image *add::apply(Image *img) {
            int w = img->width(); // Get image width
            int h = img->height(); // Get image height
            Open file = Open(filename); // Open file to add
            Image *temp =  new Image(1,1); // Create a temporary image with (1, 1)
            Image *file_img = file.apply(temp); // Create the image contained in the file
            int w_file = file_img->width(); // Get image of the file width
            int h_file = file_img->height(); // Get image of the file height

            // Iterate over all pixels of the file image
            for (int y_linha = 0; y_linha < h_file; y_linha++) {
                for (int x_linha = 0; x_linha < w_file; x_linha++) {
                    int x_final = x_linha + x; // Position x that file image pixel will take in current image
                    int y_final = y_linha + y; // Position y that file image pixel will take in current image

                    // Check if the position is within the limits of current image
                    if (x_final < w && x_final >= 0 && y_final >= 0 && y_final < h){
                        Color& c = img->at(x_final, y_final); // Get the pixel color from current image
                        Color& file_color = file_img->at(x_linha, y_linha); // Get the pixel color from file image
                        // Check if the color is not the neutral color
                        if (!(file_color.red() == neutral.red() && file_color.green() == neutral.green() && file_color.blue() == neutral.blue())) {
                            c.red() = file_color.red(); c.green() = file_color.green(); c.blue() = file_color.blue(); // Put the pixel color of the file image in current image
                        }
                    }
                }
            }
            delete file_img;
            return img;
        }

        // Copy all pixels from an image stored in  a PNG file, except pixels in that image with “neutral” color (r, g, b), to the rectangle of the current image with top-left corner (x, y) of the current image.

        std::string add::toString() const {
            std::ostringstream ss;
            ss << name() << "image added:";
            return ss.str();
        }

    }

}