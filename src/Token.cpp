#include "Token.h"

namespace cms {

    Token::Token(TokenType::_enumerated type, std::string& value) : type(type), value(value) { }

    bool Token::isType(TokenType::_enumerated tokenType) const{
        if (type == tokenType) return true;
        else return false;
    }
    const TokenType::_enumerated& Token::getType() const{
        return type;
    }
    const std::string& Token::getValue() const{
        return value;
    }
}