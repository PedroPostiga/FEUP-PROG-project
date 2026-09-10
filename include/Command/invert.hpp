#ifndef INVERT_HPP
#define INVERT_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class invert: public Command {
        public:
            invert();

            ~invert();

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif //INVERT_HPP