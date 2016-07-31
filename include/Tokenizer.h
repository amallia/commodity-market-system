#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "Token.h"

namespace cms {

    /*
     * Class Tokenizer
     *
     * This class is in charge of recognizing tokens from a given string.
     *
     */

    class Tokenizer {
    public:
        Tokenizer(const std::string &line);

        // Obtain next token of a given message
        const Token nextToken();

        // Method used to check if a token is of given type. It now it throw an exception depending on the token type
        static void expectToken(Token &token, TokenType::_enumerated type);

    private:
        std::stringstream ss;
    };
}