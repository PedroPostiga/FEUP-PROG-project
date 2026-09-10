#ifndef REPLACE_HPP
#define REPLACE_HPP

#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {
    namespace command {
        class replace: public Command {
        public:
            replace(Color &to_replace, Color &replaced);

            ~replace();

            Image *apply(Image *img) override;

            std::string toString() const override;

        private:
            Color to_replace;
            Color replaced;
        };
    }
}

#endif //REPLACE_HPP
