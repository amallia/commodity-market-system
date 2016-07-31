#include <sstream>
#include <boost/format.hpp>
#include <boost/utility.hpp>

#include "ListCommand.h"
#include "orderRepository.h"

namespace cms {
    ListCommand::ListCommand(DEALERS_IDS_ENUM::_enumerated d, boost::optional<COMMODITIES_TYPES_ENUM> c,
                             boost::optional<DEALERS_IDS_ENUM> od) : Command(d), commodity(c), ofDealer(od) { }

    boost::optional<COMMODITIES_TYPES_ENUM::_enumerated> ListCommand::getCommodity() const {
        return commodity;
    }

    boost::optional<DEALERS_IDS_ENUM::_enumerated> ListCommand::getOfDealer() const {
        return ofDealer;
    }

    std::string ListCommand::execute() const {
        std::map<OrderID, Order*> orderList = orderRepository::list();
        if (commodity && ofDealer) {
            orderList = orderRepository::list(commodity.get(), ofDealer.get());
        } else if (commodity) {
            orderList = orderRepository::list(commodity.get());
        }

        std::stringstream ss;
        for (std::map<OrderID, Order*>::iterator it = orderList.begin(); it != orderList.end(); ++it) {
            if (it->second->getAmount() > 0) {
                ss << (boost::format(order_info_string) % it->first %
                       DEALERS_IDS_ENUM::_from_integral(it->second->getDealer())._to_string() %
                       SIDES_TYPES_ENUM::_from_integral(it->second->getSide())._to_string() %
                       COMMODITIES_TYPES_ENUM::_from_integral(it->second->getCommodity())._to_string() %
                       it->second->getAmount() % it->second->getPrice()).str();
                if (boost::next(it) != orderList.end() && boost::next(it)->second->getAmount() > 0) {
                    ss << std::endl;
                }
            }
        }
        return ss.str();
    }
}