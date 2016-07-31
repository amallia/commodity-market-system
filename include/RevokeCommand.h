#pragma once

#include "Order.h"
#include "Command.h"
namespace cms {
    class RevokeCommand : public Command {

    private:
        OrderID orderID;

    public:
        RevokeCommand(DEALERS_IDS_ENUM::_enumerated d, OrderID id);
        std::string execute() const;
        OrderID getOrderID() const;

    };

}