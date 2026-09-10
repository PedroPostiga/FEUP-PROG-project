#include "ScrimParser.hpp"

#include "Command/Blank.hpp"
#include "Command/Save.hpp"
#include "Command/Open.hpp"
#include "Command/invert.hpp"
#include "Command/to_gray_scale.hpp"
#include "Command/replace.hpp"
#include "Command/fill.hpp"
#include "Command/h_mirror.hpp"
#include "Command/v_mirror.hpp"
#include "Command/move.hpp"
#include "Command/slide.hpp"
#include "Command/crop.hpp"
#include "Command/add.hpp"
#include "Command/resize.hpp"
#include "Command/rotate_left.hpp"
#include "Command/rotate_right.hpp"
#include "Command/scaleup.hpp"
#include "Command/chain.hpp"
#include "Logger.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using std::ifstream;
using std::istream;
using std::string;
using std::vector;

namespace prog {
    ScrimParser::ScrimParser() {
    };

    ScrimParser::~ScrimParser() {
    };

    Scrim *ScrimParser::parseScrim(std::istream &input) {
        // Create vector where commands will be stored
        vector<Command *> commands;

        // Parse commands while there is input in the stream
        string command_name;
        while (input >> command_name) {
            Command *command = parse_command(command_name, input);

            if (command == nullptr) {
                // Deallocate already allocated commands
                for (Command *allocated_command: commands) {
                    delete allocated_command;
                }


                *Logger::err() << "Error while parsing command\n";
                return nullptr;
            }

            commands.push_back(command);
        }

        // Create a new image pipeline
        return new Scrim(commands);
    }

    Scrim *ScrimParser::parseScrim(const std::string &filename) {
        ifstream in(filename);
        return parseScrim(in);
    }

    Command *ScrimParser::parse_command(string command_name, istream &input) {
        if (command_name == "blank") {
            // Read information for Blank command
            int w, h;
            Color fill;
            input >> w >> h >> fill;
            return new command::Blank(w, h, fill);
        }

        if (command_name == "save") {
            // Read information for Save command
            string filename;
            input >> filename;
            return new command::Save(filename);
        }

        if (command_name == "open") {
            string filename;
            input >> filename;
            return new command::Open(filename);
        }

        if (command_name == "invert") {
            return new command::invert();
        }

        if (command_name == "to_gray_scale") {
            return new command::to_gray_scale();
        }

        if (command_name == "replace") {
            Color to_replace;
            Color replaced;
            input >> to_replace >> replaced;
            return new command::replace(to_replace, replaced);
        }

        if (command_name == "fill") {
            int x, y, w, h;
            Color fill_;
            input >> x >> y >> w >> h >> fill_;
            return new command::fill(x, y, w, h, fill_);
        }

        if (command_name == "h_mirror") {
            return new command::h_mirror;
        }

        if (command_name == "v_mirror") {
            return new command::v_mirror;
        }

        if (command_name == "move") {
            int x, y;
            input >> x >> y;
            return new command::move(x, y);
        }

        if (command_name == "slide") {
            int x, y;
            input >> x >> y;
            return new command::slide(x, y);
        }

        if (command_name == "crop") {
            int x, y, w, h;
            input >> x >> y >> w >> h;
            return new command::crop(x, y, w, h);
        }

        if (command_name == "add") {
            std::string filename;
            Color neutral;
            int x, y;
            input >> filename >> neutral >> x >> y;
            return new command::add(filename, neutral, x, y);
        }

        if (command_name == "resize") {
            int x, y, w, h;
            input >> x >> y >> w >> h;
            return new command::resize(x, y, w, h);
        }

        if (command_name == "rotate_left") {
            return new command::rotate_left();
        }

        if (command_name == "rotate_right") {
            return new command::rotate_right();
        }

        if (command_name == "scaleup") {
            int x, y;
            input >> x >> y;
            return new command::scaleup(x, y);
        }

        // Iterate through the input to find the files to open until the word "end"

        if (command_name == "chain") {
            std::vector<std::string> files;
            std::string file_to_open;
            while (input >> file_to_open) {
                if (file_to_open == "end") {
                    break;
                }
                files.push_back(file_to_open);
            };
            return new command::chain(files);
        }

        *Logger::err() << "Command not recognized: '" + command_name + "'\n";
        return nullptr;
    }
}
