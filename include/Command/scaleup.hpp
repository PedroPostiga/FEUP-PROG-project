#ifndef SCALEUP_HPP
#define SCALEUP_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class scaleup: public Command {
        public:
            scaleup(int x, int y);

            ~scaleup();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int x;
            int y;
        };
    }
}

#endif //CROP_HPP
