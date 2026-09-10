#include "Color.hpp"
#include <iostream>
#include <stb/stb_image_write.h>

using std::istream;

namespace prog {
    Color::Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    //default constructor. color black value (0,0,0)

    Color::Color(const Color &c) {
        r = c.r;
        g = c.g;
        b = c.b;
    }

    //copy constructor. the result equals the value thats on object c

    Color::Color(rgb_value r, rgb_value g, rgb_value b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    //constructor that creates an object with provided values from the input (value (r, g, b))

    rgb_value Color::red() const {
        return r;
    }

    rgb_value Color::green() const {
        return g;
    }

    rgb_value Color::blue() const {
        return b;
    }

    //get immutable values for each variable of an object

    rgb_value &Color::red() {
        return r;
    }

    rgb_value &Color::green() {
        return g;
    }

    rgb_value &Color::blue() {
        return b;
    }

    //get mutable reference values for each variable of an object

}


// Use to read color values from a script file.
istream &operator>>(istream &input, prog::Color &c) {
    int r, g, b;
    input >> r >> g >> b;
    c.red() = r;
    c.green() = g;
    c.blue() = b;
    return input;
}

std::ostream &operator<<(std::ostream &output, const prog::Color &c) {
    output << (int) c.red() << ":" << (int) c.green() << ":" << (int) c.blue();
    return output;
}
