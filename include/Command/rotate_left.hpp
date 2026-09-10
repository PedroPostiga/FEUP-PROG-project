#ifndef ROTATE_LEFT_HPP
#define ROTATE_LEFT_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class rotate_left: public Command {
        public:
            rotate_left();

            ~rotate_left();

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif //ROTATE_LEFT_HPP
