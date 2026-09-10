#ifndef RESIZE_HPP
#define RESIZE_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class resize: public Command {
        public:
            resize(int x, int y, int w, int h);

            ~resize();

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

#endif //RESIZE_HPP
