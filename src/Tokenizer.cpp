#include <boost/format.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>

#include "Tokenizer.h"
#include "Dealer.h"
#include "Command.h"
#include "Side.h"
#include "Commodity.h"
#include "utils.h"
#include "ParseException.h"

namespace cms {

    Tokenizer::Tokenizer(const std::string &line) : ss(line) { }

    const Token Tokenizer::nextToken() {
        std::string tokenValue;

        if (ss >> tokenValue) {
            if (Dealer::isDealer(tokenValue)) {
                return Token(TokenType::dealer_id, tokenValue);
#define COMMAND_BODY(R, DATA, T)                                   \
            } else if (tokenValue == BOOST_PP_STRINGIZE(T)) {             \
                return Token(TokenType::command, tokenValue);
            BOOST_PP_SEQ_FOR_EACH(COMMAND_BODY, _, COMMAND_TYPES);
#undef COMMAND_BODY
            } else if (Commodity::isCommodity(tokenValue)) {
                return Token(TokenType::commodity, tokenValue);
#define SIDES_BODY(R, DATA, T)                                   \
            } else if (tokenValue == BOOST_PP_STRINGIZE(T)) {             \
                return Token(TokenType::side, tokenValue);
            BOOST_PP_SEQ_FOR_EACH(SIDES_BODY, _, SIDES_TYPES);
#undef SIDES_BODY
            }
            else if (isInteger(tokenValue)) {
                return Token(TokenType::integer_token, tokenValue);
            }
            else if (isDouble(tokenValue)) {
                return Token(TokenType::double_token, tokenValue);
            }
            return Token(TokenType::unknown, tokenValue);
        } else {
            return Token(TokenType::end, tokenValue);
        }
    }

    void Tokenizer::expectToken(Token &token, TokenType::_enumerated type) {
        if (!token.isType(type)) {
            if (type == TokenType::commodity) {
                throw ParseException("UNKNOWN_COMMODITY");
            } else if (type == TokenType::dealer_id) {
                throw ParseException("UNKNOWN_DEALER");
            }
            throw ParseException("INVALID_MESSAGE");
        }
    }
}
