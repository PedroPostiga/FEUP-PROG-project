#ifndef SLIDE_HPP
#define SLIDE_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class slide: public Command {
        public:
            slide(int x, int y);

            ~slide();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int x;
            int y;
        };
    }
}

#endif //SLIDE_HPP
