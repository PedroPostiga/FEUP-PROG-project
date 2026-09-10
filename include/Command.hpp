#ifndef PROJECT_COMMAND_HPP
#define PROJECT_COMMAND_HPP

#include "Image.hpp"

#include <string>

namespace prog {
    //    namespace command {


    class Command {
    public:
        Command(std::string command_name);

        virtual ~Command() = 0;

        /**
         * Applies this command to an image.
         *
         * @param img
         * @return the image after the command (can be the same pointer or a new one).
         * If a new pointer is returned, the previous one is deleted.
         */
        virtual Image *apply(Image *img) = 0;

        /**
         *
         * @return string representation of this command, for printing
         */
        virtual std::string toString() const;

        std::string name() const;

        //void Image::invert(Image* img);

        //void Image::to_gray_scale(Image* img);

    private:
        std::string command_name;
    };

}

std::ostream &operator<<(std::ostream &output, const prog::Command &command);


#endif //PROJECT_COMMAND_HPP
