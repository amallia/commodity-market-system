#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "CLI.h"
#include "Command.h"
#include "ParseException.h"

namespace cms {
    void CLI::run() {
        std::string line;
        std::cout << "Type 'q' or 'quit' and then hit return to quit the program" << std::endl;
        while (1) {
            std::cout << "> ";
            std::getline(std::cin, line);
            if (boost::iequals(line, "q") || boost::iequals(line,"quit")) {
                break;
            }
            std::cout << Input::commandExecute(line);
        }
    }
}