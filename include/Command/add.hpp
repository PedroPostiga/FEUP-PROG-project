#ifndef ADD_HPP
#define ADD_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class add: public Command {
        public:
            add(std::string filename, Color neutral, int x, int y);

            ~add();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            std::string filename;
            Color neutral;
            int x;
            int y;
        };
    }
}

#endif //ADD_HPP
