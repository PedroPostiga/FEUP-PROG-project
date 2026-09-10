#ifndef FILL_HPP
#define FILL_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class fill: public Command {
        public:
            fill(int x, int y, int w, int h, Color &fill_);

            ~fill();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int x;
            int y;
            int w;
            int h;
            Color fill_;
        };
    }
}

#endif //FILL_HPP
