#ifndef CHAIN_HPP
#define CHAIN_HPP

#include <string>
#include "Command.hpp"
#include "Image.hpp"
#include "Color.hpp"

namespace prog {

    namespace command {

        class chain: public Command {
        public:

            chain(std::vector<std::string> files);

            ~chain();

            Image* apply(Image* img) override;  // override base method

            Image* apply(Image* img, std::vector<std::string>& files_opened);  // your extended version

            std::string toString() const override;

        private:

            std::vector<std::string> files;

        };
    }
}

#endif //CHAIN_HPP
