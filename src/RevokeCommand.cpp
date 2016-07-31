#include <boost/format.hpp>

#include "RevokeCommand.h"
#include "orderRepository.h"
#include "OrderNotFoundException.h"
namespace cms {
    RevokeCommand::RevokeCommand(DEALERS_IDS_ENUM::_enumerated d, OrderID id) : Command(d), orderID(id) { };

    OrderID RevokeCommand::getOrderID() const{
        return orderID;
    }

    std::string RevokeCommand::execute() const{
        try {
            Order o = orderRepository::findOne(orderID);
            if (o.getDealer() == getDealerID()) {
                orderRepository::remove(orderID);
                return (boost::format(revoke_string) % orderID).str();
            } else {
                return "UNAUTHORIZED";

            }
        } catch (OrderNotFoundException e) {
            return e.what();
        }

    }
}