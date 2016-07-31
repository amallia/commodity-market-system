#include <boost/format.hpp>
#include <iostream>

#include "PostCommand.h"
#include "orderRepository.h"

namespace cms {

    PostCommand::PostCommand(DEALERS_IDS_ENUM::_enumerated d, SIDES_TYPES_ENUM::_enumerated s,
                             COMMODITIES_TYPES_ENUM::_enumerated c,
                             Amount a, Price p) : Command(d), side(s), commodity(c), amount(a), price(p) { }

    Amount PostCommand::getAmount() const{
        return amount;
    }

    Price PostCommand::getPrice() const{
        return price;
    }

    SIDES_TYPES_ENUM::_enumerated PostCommand::getSide() const{
        return side;
    }

    COMMODITIES_TYPES_ENUM::_enumerated PostCommand::getCommodity() const{
        return commodity;
    }

    std::string PostCommand::execute() const{
        DEALERS_IDS_ENUM dealer = getDealerID();
        Order o(dealer, side, commodity, amount, price);
        OrderID id = orderRepository::add(o);

        return (boost::format(post_string) % id %
                DEALERS_IDS_ENUM::_from_integral(o.getDealer())._to_string() %
                SIDES_TYPES_ENUM::_from_integral(o.getSide())._to_string() %
                COMMODITIES_TYPES_ENUM::_from_integral(o.getCommodity())._to_string() % o.getAmount() %
                o.getPrice()).str();
    }

}