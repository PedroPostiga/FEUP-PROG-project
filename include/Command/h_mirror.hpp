#ifndef H_MIRROR_HPP
#define H_MIRROR_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class h_mirror: public Command {
        public:
            h_mirror();

            ~h_mirror();

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif //H_MIRROR_HPP
