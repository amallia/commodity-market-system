#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Parser

#include <boost/test/unit_test.hpp>
#include <boost/utility.hpp>

#include "AggressCommand.h"
#include "PostCommand.h"
#include "CheckCommand.h"
#include "ListCommand.h"
#include "RevokeCommand.h"
#include "parser.h"
#include "ParseException.h"

namespace cms {
    namespace test {


        bool invalidMessage(ParseException const &ex) {
            BOOST_CHECK_EQUAL(ex.what(), "INVALID_MESSAGE");
            return true;
        }


        bool unknownDealer(ParseException const &ex) {
            BOOST_CHECK_EQUAL(ex.what(), "UNKNOWN_DEALER");
            return true;
        }

        bool unknownCommodity(ParseException const &ex) {
            BOOST_CHECK_EQUAL(ex.what(), "UNKNOWN_COMMODITY");
            return true;
        }

        BOOST_AUTO_TEST_CASE(wrongMessages) {

            //Too long
            BOOST_CHECK_EXCEPTION(parser::parse_message(std::string(COMMAND_LIMIT + 1, 'a')), ParseException,
                                  invalidMessage);
            //Empty
            BOOST_CHECK_EXCEPTION(parser::parse_message(""), ParseException, invalidMessage);

            //Invalid command
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB GET SELL GOLD 1000000 1174.6"), ParseException,
                                  invalidMessage);

            // Missing command
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB "), ParseException, invalidMessage);

            // Unknown dealer
            BOOST_CHECK_EXCEPTION(parser::parse_message("AB POST SELL GOLD 1000000 1174.6"), ParseException,
                                  unknownDealer);
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB LIST SILV AB"), ParseException, unknownDealer);

            // Unknow Commodity
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB POST SELL BEEF 1000000 1174.6"), ParseException,
                                  unknownCommodity);
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB LIST BEEF"), ParseException,
                                  unknownCommodity);

            // Unknown side
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB POST GIVE GOLD 1000000 1174.6"), ParseException,
                                  invalidMessage);
            // Invalid amount
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB POST BUY GOLD 3.1 1174.6"), ParseException,
                                  invalidMessage);
            // Missing amount
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB POST GIVE GOLD 1174.6"), ParseException, invalidMessage);
            // Price passed as integer
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB POST BUY GOLD 1000000 10"), ParseException,
                                  invalidMessage);
            // Missing price
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB POST BUY GOLD 1000000"), ParseException, invalidMessage);

            // Invalid Order ID
            BOOST_CHECK_EXCEPTION(parser::parse_message("DB REVOKE 1.1"), ParseException, invalidMessage);

        }

        BOOST_AUTO_TEST_CASE(parsePost) {
            BOOST_CHECK_NO_THROW(boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST SELL GOLD 1000000 1174.6")));
            boost::shared_ptr<PostCommand> command = boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST SELL GOLD 1000000 1174.6"));
            BOOST_CHECK_EQUAL(command->getDealerID(), DEALERS_IDS_ENUM::DB);
            BOOST_CHECK_EQUAL(command->getSide(), SIDES_TYPES_ENUM::SELL);
            BOOST_CHECK_EQUAL(command->getCommodity(), COMMODITIES_TYPES_ENUM::GOLD);
            BOOST_CHECK_EQUAL(command->getAmount(), 1000000);
            BOOST_CHECK_EQUAL(command->getPrice(), 1174.6);
            command = boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST BUY GOLD 1000000 1174.6"));
            BOOST_CHECK_EQUAL(command->getSide(), SIDES_TYPES_ENUM::BUY);
            command = boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST SELL SILV 1000000 1174.6"));
            BOOST_CHECK_EQUAL(command->getCommodity(), COMMODITIES_TYPES_ENUM::SILV);
            command = boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST SELL PORK 1000000 1174.6"));
            BOOST_CHECK_EQUAL(command->getCommodity(), COMMODITIES_TYPES_ENUM::PORK);
            command = boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST SELL RICE 1000000 1174.6"));
            BOOST_CHECK_EQUAL(command->getCommodity(), COMMODITIES_TYPES_ENUM::RICE);
            command = boost::dynamic_pointer_cast<PostCommand>(
                    parser::parse_message("DB POST SELL OIL 1000000 1174.6"));
            BOOST_CHECK_EQUAL(command->getCommodity(), COMMODITIES_TYPES_ENUM::OIL);

        }

        BOOST_AUTO_TEST_CASE(parseList) {
            BOOST_CHECK_NO_THROW(boost::dynamic_pointer_cast<ListCommand>(
                    parser::parse_message("DB LIST")));
            boost::shared_ptr<ListCommand> command = boost::dynamic_pointer_cast<ListCommand>(
                    parser::parse_message("DB LIST"));
            BOOST_CHECK_EQUAL(command->getDealerID(), DEALERS_IDS_ENUM::DB);
            command = boost::dynamic_pointer_cast<ListCommand>(
                    parser::parse_message("DB LIST GOLD"));
            BOOST_CHECK_EQUAL(command->getCommodity().get(), COMMODITIES_TYPES_ENUM::GOLD);
            command = boost::dynamic_pointer_cast<ListCommand>(
                    parser::parse_message("DB LIST GOLD JPM"));
            BOOST_CHECK_EQUAL(command->getCommodity().get(), COMMODITIES_TYPES_ENUM::GOLD);
            BOOST_CHECK_EQUAL(command->getOfDealer().get(), DEALERS_IDS_ENUM::JPM);
        }

        BOOST_AUTO_TEST_CASE(parseRevoke) {
            BOOST_CHECK_NO_THROW(boost::dynamic_pointer_cast<RevokeCommand>(
                    parser::parse_message("DB REVOKE 123")));
            boost::shared_ptr<RevokeCommand> command = boost::dynamic_pointer_cast<RevokeCommand>(
                    parser::parse_message("DB REVOKE 123"));
            BOOST_CHECK_EQUAL(command->getOrderID(), 123);
        }

        BOOST_AUTO_TEST_CASE(parseCheck) {
            BOOST_CHECK_NO_THROW(boost::dynamic_pointer_cast<CheckCommand>(
                    parser::parse_message("DB CHECK 123")));
            boost::shared_ptr<CheckCommand> command = boost::dynamic_pointer_cast<CheckCommand>(
                    parser::parse_message("DB CHECK 123"));
            BOOST_CHECK_EQUAL(command->getOrderID(), 123);
        }

        BOOST_AUTO_TEST_CASE(parseAggress) {
            BOOST_CHECK_NO_THROW(boost::dynamic_pointer_cast<AggressCommand>(
                    parser::parse_message("DB AGGRESS 1 10000")));
            // Parse single aggress
            boost::shared_ptr<AggressCommand> command = boost::dynamic_pointer_cast<AggressCommand>(
                    parser::parse_message("DB AGGRESS 1 10000"));
            BOOST_CHECK_EQUAL(command->orderAmountList().size(), 1);
            BOOST_CHECK_EQUAL(command->orderAmountList()[1], 10000);

            // Parse multi aggress
            command = boost::dynamic_pointer_cast<AggressCommand>(
                    parser::parse_message("DB AGGRESS 1 10000 2 3000 5 5000"));
            BOOST_CHECK_EQUAL(command->orderAmountList().size(), 3);
            BOOST_CHECK_EQUAL(command->orderAmountList()[1], 10000);
            BOOST_CHECK_EQUAL(command->orderAmountList()[2], 3000);
            BOOST_CHECK_EQUAL(command->orderAmountList()[5], 5000);
        }
    }
}