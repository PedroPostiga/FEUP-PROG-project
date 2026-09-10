#include "Command/chain.hpp"
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "Image.hpp"
#include "Color.hpp"
#include "ScrimParser.hpp"
#include <sstream>

namespace prog {

    namespace command {

        chain::chain(std::vector<std::string> files) : Command("chain"), files(std::move(files)) {} // Constructor

        chain::~chain() {} // Destructor

        // Entry point to apply the chain command
        Image* chain::apply(Image* img) {
            std::vector<std::string> files_opened; // Create an empty vector to check already opened files
            return apply(img, files_opened);
        }

        Image *chain::apply(Image *img, std::vector<std::string>& files_opened) {
            ScrimParser scrimparser; // Parser for the script files

            // Iterate over all commands
            for (std::string& command_in_scrim : files) {

                if (std::find(files_opened.begin(), files_opened.end(), command_in_scrim) != files_opened.end()) { // Skip the file if it has been opened befora
                    continue;
                }
                files_opened.push_back(command_in_scrim); // Put the file in check list (files_opened)

                Scrim* parse_scrim = scrimparser.parseScrim(command_in_scrim); // Parse the scrim file into a scrim object

                auto commands = parse_scrim->getCommands(); // Get the vector with commands from ScrimParser

                for (Command*& command_to_apply: commands) {
                    if (command_to_apply->name() == "Blank" || command_to_apply->name() == "Open" || command_to_apply->name() == "Save") { // Skip commands that should be ignored
                        continue;
                    }
                    if (command_to_apply->name() == "chain") {

                        /* Trying to cast the command to a chain object using dynamic_cast
                        * If the cast succeeds, the object gets attributed a valid pointer value
                        * If not, it returns nullptr */

                        chain* chain_recursive = dynamic_cast<chain*>(command_to_apply);

                        // Check if chain recursive is not nullptr
                        if (chain_recursive) {
                            img = chain_recursive->apply(img, files_opened); // Recursive call to chain command
                        }
                    }
                    else {
                        img = command_to_apply->apply(img); // Apply other commands
                    }
                }
                delete parse_scrim;
                files_opened.pop_back(); // Remove file from files_opened
            }
            return img;
        }

        std::string chain::toString() const {
            std::ostringstream ss;
            ss << name() << "chained commands applied to image:";
            return ss.str();
        }

    }
}