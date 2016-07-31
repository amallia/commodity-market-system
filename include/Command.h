#pragma once

#include <string>
#include <enum.h>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/shared_ptr.hpp>

#include "Dealer.h"

namespace cms {

    #define COMMAND_LIMIT 255
    #define COMMAND_TYPES (POST)(REVOKE)(CHECK)(LIST)(AGGRESS)
    BETTER_ENUM(COMMANDS_TYPES_ENUM, int, BOOST_PP_SEQ_ENUM(COMMAND_TYPES))


    /*
     * Class Command
     *
     * This class represents a command object, which is a base type of the specialized ones.
     * All commands share a Dealer ID who executed the command.
     *
     */

    class Command {

    public:
        Command(DEALERS_IDS_ENUM::_enumerated d);

        DEALERS_IDS_ENUM::_enumerated getDealerID() const;

        virtual std::string execute() const = 0;

    protected:
        static const std::string order_info_string;
        static const std::string post_string;
        static const std::string aggress_string;
        static const std::string revoke_string;
        static const std::string filled_string;
    private:
        DEALERS_IDS_ENUM::_enumerated dealerID;
    };
}