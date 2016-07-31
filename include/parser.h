#pragma once

#include <string>
#include <boost/shared_ptr.hpp>

#include "Command.h"
#include "Tokenizer.h"


namespace cms {
    namespace parser {

        boost::shared_ptr<Command> parse_POST(Tokenizer &tokenizer);

        boost::shared_ptr<Command> parse_REVOKE(Tokenizer &tokenizer);

        boost::shared_ptr<Command> parse_CHECK(Tokenizer &tokenizer);

        boost::shared_ptr<Command> parse_LIST(Tokenizer &tokenizer);

        boost::shared_ptr<Command> parse_AGGRESS(Tokenizer &tokenizer);

        boost::shared_ptr<cms::Command> parse_message(std::string line);

    }
}