#ifndef V_MIRROR_HPP
#define V_MIRROR_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class v_mirror: public Command {
        public:
            v_mirror();

            ~v_mirror();

            Image *apply(Image *img) override;

            std::string toString() const override;
        };
    }
}

#endif //V_MIRROR_HPP
