#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Orders

#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include "Dealer.h"
#include "Commodity.h"
#include "Side.h"
#include "Command.h"
#include "PostCommand.h"
#include "RevokeCommand.h"
#include "CheckCommand.h"
#include "ListCommand.h"
#include "AggressCommand.h"

namespace cms {
    namespace test {
        boost::shared_ptr<Command> command_ptr;

        BOOST_AUTO_TEST_CASE(postCommand) {
            command_ptr = boost::shared_ptr<Command>(
                    new PostCommand(DEALERS_IDS_ENUM::DB, SIDES_TYPES_ENUM::SELL,
                                    COMMODITIES_TYPES_ENUM::GOLD, 1000000, 1174.6));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "1 DB SELL GOLD 1000000 1174.6 HAS BEEN POSTED");
        }

        BOOST_AUTO_TEST_CASE(revokeCommand) {
            // Unauthorized revoke
            command_ptr = boost::shared_ptr<Command>(
                    new RevokeCommand(DEALERS_IDS_ENUM::JPM, 1));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "UNAUTHORIZED");
            // Revoke non existing order
            command_ptr = boost::shared_ptr<Command>(
                    new RevokeCommand(DEALERS_IDS_ENUM::JPM, 2));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "UNKNOWN_ORDER");
            // Working revoke
            command_ptr = boost::shared_ptr<Command>(
                    new RevokeCommand(DEALERS_IDS_ENUM::DB, 1));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "1 HAS BEEN REVOKED");

        }

        BOOST_AUTO_TEST_CASE(listCommand) {
            // Empty list
            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB, boost::none, boost::none));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "");

            // Post order
            command_ptr = boost::shared_ptr<Command>(
                    new PostCommand(DEALERS_IDS_ENUM::CITI, SIDES_TYPES_ENUM::SELL,
                                    COMMODITIES_TYPES_ENUM::GOLD, 1000000, 1174.6));
            command_ptr->execute();

            // List single order
            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB, boost::none, boost::none));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "2 CITI SELL GOLD 1000000 1174.6");

            // Post order
            command_ptr = boost::shared_ptr<Command>(
                    new PostCommand(DEALERS_IDS_ENUM::JPM, SIDES_TYPES_ENUM::SELL,
                                    COMMODITIES_TYPES_ENUM::SILV, 1000000, 1174.6));
            command_ptr->execute();

            // List multiple orders
            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB, boost::none, boost::none));
            BOOST_CHECK_EQUAL(command_ptr->execute(),
                              "2 CITI SELL GOLD 1000000 1174.6\n3 JPM SELL SILV 1000000 1174.6");

            // Filter by commodity
            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB,
                                                                     boost::optional<COMMODITIES_TYPES_ENUM>(
                                                                             COMMODITIES_TYPES_ENUM::GOLD),
                                                                     boost::none));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "2 CITI SELL GOLD 1000000 1174.6");

            // Post order
            command_ptr = boost::shared_ptr<Command>(
                    new PostCommand(DEALERS_IDS_ENUM::BOFA, SIDES_TYPES_ENUM::BUY,
                                    COMMODITIES_TYPES_ENUM::SILV, 1000000, 1174.6));
            command_ptr->execute();

            // Filter by commodity
            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB,
                                                                     boost::optional<COMMODITIES_TYPES_ENUM>(
                                                                             COMMODITIES_TYPES_ENUM::SILV),
                                                                     boost::optional<DEALERS_IDS_ENUM>(
                                                                             DEALERS_IDS_ENUM::BOFA)));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "4 BOFA BUY SILV 1000000 1174.6");

        }

        BOOST_AUTO_TEST_CASE(aggressCommand) {

            // Aggress single order
            std::map<OrderID, Amount> o_a;
            o_a.insert(std::make_pair(4, 500000));
            command_ptr = boost::shared_ptr<Command>(new AggressCommand(DEALERS_IDS_ENUM::DB, o_a));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "SOLD 500000 SILV @ 1174.6 FROM BOFA");

            command_ptr = boost::shared_ptr<Command>(
                    new ListCommand(DEALERS_IDS_ENUM::DB,
                                    boost::optional<COMMODITIES_TYPES_ENUM>(COMMODITIES_TYPES_ENUM::SILV),
                                    boost::optional<DEALERS_IDS_ENUM>(DEALERS_IDS_ENUM::BOFA)));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "4 BOFA BUY SILV 500000 1174.6");

            // Aggress multiple orders
            o_a.clear();
            o_a.insert(std::make_pair(2, 500000));
            o_a.insert(std::make_pair(3, 500000));
            o_a.insert(std::make_pair(4, 100000));
            command_ptr = boost::shared_ptr<Command>(new AggressCommand(DEALERS_IDS_ENUM::DB, o_a));
            BOOST_CHECK_EQUAL(command_ptr->execute(),
                              "BOUGHT 500000 GOLD @ 1174.6 FROM CITI\nBOUGHT 500000 SILV @ 1174.6 FROM JPM\nSOLD 100000 SILV @ 1174.6 FROM BOFA");

            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB, boost::none, boost::none));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "2 CITI SELL GOLD 500000 1174.6\n3 JPM SELL SILV 500000 1174.6\n4 BOFA BUY SILV 400000 1174.6");


            // Aggress not existing order
            o_a.clear();
            o_a.insert(std::make_pair(8, 500000));
            command_ptr = boost::shared_ptr<Command>(new AggressCommand(DEALERS_IDS_ENUM::DB, o_a));
            BOOST_CHECK_EQUAL(command_ptr->execute(),"UNKNOWN_ORDER");


            // Aggress not existing order
            o_a.clear();
            o_a.insert(std::make_pair(4, 10000000000));
            command_ptr = boost::shared_ptr<Command>(new AggressCommand(DEALERS_IDS_ENUM::DB, o_a));
            BOOST_CHECK_EQUAL(command_ptr->execute(),"INVALID_MESSAGE");

        }

        BOOST_AUTO_TEST_CASE(checkCommand) {

            // Post order
            command_ptr = boost::shared_ptr<Command>(
                    new PostCommand(DEALERS_IDS_ENUM::CITI, SIDES_TYPES_ENUM::SELL,
                                    COMMODITIES_TYPES_ENUM::GOLD, 1000000, 1174.6));
            command_ptr->execute();

            // Unauthorized check
            command_ptr = boost::shared_ptr<Command>(new CheckCommand(DEALERS_IDS_ENUM::DB, 5));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "UNAUTHORIZED");

            // Check not existing order
            command_ptr = boost::shared_ptr<Command>(new CheckCommand(DEALERS_IDS_ENUM::CITI, 7));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "UNKNOWN_ORDER");

            // Check order
            command_ptr = boost::shared_ptr<Command>(new CheckCommand(DEALERS_IDS_ENUM::CITI, 5));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "5 CITI SELL GOLD 1000000 1174.6");

            // Aggress order
            std::map<OrderID, Amount> o_a;
            o_a.insert(std::make_pair(5, 1000000));
            command_ptr = boost::shared_ptr<Command>(new AggressCommand(DEALERS_IDS_ENUM::DB, o_a));
            command_ptr->execute();

            // Check filled order
            command_ptr = boost::shared_ptr<Command>(new CheckCommand(DEALERS_IDS_ENUM::CITI, 5));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "5 HAS BEEN FILLED");

            command_ptr = boost::shared_ptr<Command>(new ListCommand(DEALERS_IDS_ENUM::DB, boost::none, boost::none));
            BOOST_CHECK_EQUAL(command_ptr->execute(), "2 CITI SELL GOLD 500000 1174.6\n3 JPM SELL SILV 500000 1174.6\n4 BOFA BUY SILV 400000 1174.6");


        }


    }
}