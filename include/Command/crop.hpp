#ifndef CROP_HPP
#define CROP_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class crop: public Command {
        public:
            crop(int x, int y, int w, int h);

            ~crop();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int x;
            int y;
            int w;
            int h;
        };
    }
}

#endif //CROP_HPP
