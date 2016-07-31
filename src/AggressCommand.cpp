#include <sstream>
#include <boost/format.hpp>

#include "AggressCommand.h"
#include "orderRepository.h"
#include "OrderNotFoundException.h"

namespace cms {
    AggressCommand::AggressCommand(DEALERS_IDS_ENUM::_enumerated d, std::map<OrderID, Amount> o_a) : Command(d),
                                                                                                             order_amount(o_a) { };

    std::string AggressCommand::execute() const{
        std::stringstream ss;
        for (std::map<OrderID, Amount>::const_iterator it = order_amount.begin(); it != order_amount.end(); ++it) {
            try {
                Order &o = orderRepository::findOne(it->first);
                if (o.getAmount() >= it->second) {
                    o.reduce(it->second);
                    ss << (boost::format("%1% %2% %3% @ %4% FROM %5%") %
                           (o.getSide() == SIDES_TYPES_ENUM::SELL ? "BOUGHT" : "SOLD") %
                           it->second % COMMODITIES_TYPES_ENUM::_from_integral(o.getCommodity())._to_string() % o.getPrice() %
                           DEALERS_IDS_ENUM::_from_integral(o.getDealer())._to_string());
                    if (boost::next(it) != order_amount.end()) {
                        ss << std::endl;
                    }
                }
                else {
                    ss << "INVALID_MESSAGE";
                }
            } catch (OrderNotFoundException e) {
                ss << e.what();
            }
        }


        return ss.str();
    }

   std::map<OrderID, Amount> AggressCommand::orderAmountList() const{
        return order_amount;
    };
}