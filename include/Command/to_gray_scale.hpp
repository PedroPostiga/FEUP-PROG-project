#ifndef TO_GRAY_SCALE_HPP
#define TO_GRAY_SCALE_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class to_gray_scale: public Command {
        public:
            to_gray_scale();

            ~to_gray_scale();

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif //TO_GRAY_SCALE_HPP
