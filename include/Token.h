#pragma once

#include <string>
#include "enum.h"

namespace cms {

    BETTER_ENUM(TokenType, int, dealer_id, command, side, commodity, integer_token, double_token, end, unknown);

    /*
     * Class Token
     *
     * This class represents a token object, which is generate by the Tokenizer
     * and used by the parser to check the correct message syntax.
     * A token is composed by a type and the actual string value.
     * Token types are previously defined using an enum.
     *
     */

    class Token {
    public:
        Token(TokenType::_enumerated type, std::string& value);

        // Used to check if token type corresponds to the one provided
        bool isType(TokenType::_enumerated type) const;

        const std::string &getValue() const;

    private:
        TokenType::_enumerated type;
        std::string value;
    };
}