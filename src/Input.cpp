#include <iostream>
#include <sstream>
#include "Command.h"
#include "parser.h"
#include "Input.h"
#include "ParseException.h"

namespace cms {
    std::string Input::commandExecute(std::string s) {
        std::stringstream ss;
        try {
            boost::shared_ptr<Command> command_ptr = parser::parse_message(std::string(s));
            std::string output = command_ptr->execute();
            ss << output;
            if (!output.empty()) ss << std::endl;
        } catch (ParseException e) {
            ss << e.what() << std::endl;
        }
        return ss.str();
    }

}