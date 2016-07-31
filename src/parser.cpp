#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/format.hpp>

#include "Order.h"
#include "Dealer.h"
#include "Command.h"
#include "PostCommand.h"
#include "AggressCommand.h"
#include "CheckCommand.h"
#include "ListCommand.h"
#include "RevokeCommand.h"
#include "parser.h"
#include "ParseException.h"
#include "utils.h"

namespace cms {

    namespace parser {

        boost::shared_ptr<Command> parse_POST(Tokenizer &tokenizer, DEALERS_IDS_ENUM::_enumerated dealer) {
            Token token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::side);
            SIDES_TYPES_ENUM side = SIDES_TYPES_ENUM::_from_string(token.getValue().c_str());

            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::commodity);
            COMMODITIES_TYPES_ENUM commodity = COMMODITIES_TYPES_ENUM::_from_string(token.getValue().c_str());

            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::integer_token);
            Amount amount = toInt(token.getValue());

            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::double_token);
            Price price = toDouble(token.getValue());
            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::end);
            boost::shared_ptr<PostCommand> command(new PostCommand(dealer, side, commodity, amount, price));
            return command;
        }

        boost::shared_ptr<Command> parse_REVOKE(Tokenizer &tokenizer, DEALERS_IDS_ENUM::_enumerated dealer) {

            Token token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::integer_token);
            OrderID orderID = toInt(token.getValue());
            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::end);
            boost::shared_ptr<RevokeCommand> command(new RevokeCommand(dealer, orderID));
            return command;
        };

        boost::shared_ptr<Command> parse_CHECK(Tokenizer &tokenizer, DEALERS_IDS_ENUM::_enumerated dealer) {

            Token token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::integer_token);
            OrderID orderID = toInt(token.getValue());
            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::end);
            boost::shared_ptr<CheckCommand> command(new CheckCommand(dealer, orderID));
            return command;

        };

        boost::shared_ptr<Command> parse_LIST(Tokenizer &tokenizer, DEALERS_IDS_ENUM::_enumerated dealer) {
            Token token = tokenizer.nextToken();
            boost::optional<COMMODITIES_TYPES_ENUM> commodity_opt;
            boost::optional<DEALERS_IDS_ENUM> dealer_opt;
            if (!token.isType(TokenType::end)) {
                Tokenizer::expectToken(token, TokenType::commodity);
                commodity_opt = COMMODITIES_TYPES_ENUM::_from_string(token.getValue().c_str());
                token = tokenizer.nextToken();
                if (!token.isType(TokenType::end)) {
                    Tokenizer::expectToken(token, TokenType::dealer_id);
                    dealer_opt = DEALERS_IDS_ENUM::_from_string(token.getValue().c_str());
                    token = tokenizer.nextToken();
                }
            }
            Tokenizer::expectToken(token, TokenType::end);
            boost::shared_ptr<ListCommand> command(new ListCommand(dealer, commodity_opt, dealer_opt));
            return command;
        };

        boost::shared_ptr<Command> parse_AGGRESS(Tokenizer &tokenizer, DEALERS_IDS_ENUM::_enumerated dealer) {
            Token token = tokenizer.nextToken();
            std::map<OrderID, Amount> order_amount;
            do {
                Tokenizer::expectToken(token, TokenType::integer_token);
                OrderID order = toInt(token.getValue());
                token = tokenizer.nextToken();
                Tokenizer::expectToken(token, TokenType::integer_token);
                Amount amount = toInt(token.getValue());
                order_amount.insert(std::pair<OrderID, Amount>(order, amount));
                token = tokenizer.nextToken();
            } while (!token.isType(TokenType::end));
            Tokenizer::expectToken(token, TokenType::end);
            boost::shared_ptr<AggressCommand> command(new AggressCommand(dealer, order_amount));
            return command;
        };


        boost::shared_ptr<Command> parse_message(std::string line) {
            if (line.length() == 0 || line.length() > COMMAND_LIMIT) {
                throw ParseException("INVALID_MESSAGE");
            }
            Tokenizer tokenizer(line);
            Token token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::dealer_id);
            DEALERS_IDS_ENUM dealer = DEALERS_IDS_ENUM::_from_string(token.getValue().c_str());
            token = tokenizer.nextToken();
            Tokenizer::expectToken(token, TokenType::command);
            if (false) {
#define LOOP_BODY(R, DATA, T)                                   \
        } else if (token.getValue() == BOOST_PP_STRINGIZE(T)) {             \
            return BOOST_PP_CAT(parser::parse_, T)(tokenizer, dealer);
            BOOST_PP_SEQ_FOR_EACH(LOOP_BODY, _, COMMAND_TYPES);
#undef LOOP_BODY
            }else{
                throw ParseException("INVALID_MESSAGE");
            }
        }
    }
}