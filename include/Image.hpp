#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__

#include "Color.hpp"
#include <vector>

namespace prog {
    class Image {
    private:
        int h;
        int w;
        std::vector<std::vector<Color>> pixel_matrix;

		// variables to represent width(w) and height(h) and a vector of the rgb color of all pixels
    
	public:
        Image(int w, int h, const Color &fill = {255, 255, 255});

        ~Image();

        int width() const;

        int height() const;

        Color &at(int x, int y);

        const Color &at(int x, int y) const;
    };
}
#endif
