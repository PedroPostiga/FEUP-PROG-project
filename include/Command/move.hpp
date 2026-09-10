#ifndef MOVE_HPP
#define MOVE_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class move: public Command {
        public:
            move(int x, int y);

            ~move();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            int x;
            int y;
        };
    }
}

#endif //MOVE_HPP
