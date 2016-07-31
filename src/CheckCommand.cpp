#include <boost/format.hpp>
#include <OrderNotFoundException.h>
#include "CheckCommand.h"
#include "orderRepository.h"

namespace cms {
    CheckCommand::CheckCommand(DEALERS_IDS_ENUM::_enumerated d, OrderID id) : Command(d), orderID(id) { };

    OrderID CheckCommand::getOrderID() const{
        return orderID;
    }

    std::string CheckCommand::execute() const{
        try {
            Order &o = orderRepository::findOne(orderID);
            if (o.getDealer() == getDealerID()) {
                if (o.getAmount() > 0) {
                    return (boost::format(order_info_string) % orderID %
                            DEALERS_IDS_ENUM::_from_integral(o.getDealer())._to_string() %
                            SIDES_TYPES_ENUM::_from_integral(o.getSide())._to_string() %
                            COMMODITIES_TYPES_ENUM::_from_integral(o.getCommodity())._to_string() % o.getAmount() %
                            o.getPrice()).str();
                } else {
                    return (boost::format(filled_string) % orderID).str();
                }

            } else {
                return "UNAUTHORIZED";
            }
        } catch (OrderNotFoundException e) {
            return e.what();
        }
    }
}