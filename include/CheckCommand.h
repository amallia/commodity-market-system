#pragma once

#include "Order.h"
#include "Command.h"

namespace cms {

    class CheckCommand : public Command {
    private:
        OrderID orderID;
    public:
        CheckCommand(DEALERS_IDS_ENUM::_enumerated d, OrderID id);

        OrderID getOrderID() const;

        std::string execute() const;

    };
}