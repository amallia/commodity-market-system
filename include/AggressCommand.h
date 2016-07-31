#pragma once

#include <map>
#include <boost/utility.hpp>

#include "Order.h"
#include "Command.h"

namespace cms {

    class AggressCommand : public Command {
    private:

        static const std::string aggressString;

        std::map<OrderID, Amount> order_amount;

    public:
        AggressCommand(DEALERS_IDS_ENUM::_enumerated d, std::map<OrderID, Amount> o_a);

        std::string execute() const;

        std::map<OrderID, Amount> orderAmountList() const;

    };
}