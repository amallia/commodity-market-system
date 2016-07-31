#include "Order.h"

namespace cms {
    Order::Order() { }

    Order::Order(DEALERS_IDS_ENUM::_enumerated d, SIDES_TYPES_ENUM::_enumerated s,
                 COMMODITIES_TYPES_ENUM::_enumerated c, Amount a, Price p) : dealer(d), side(s), commodity(c),
                                                                           amount(a), price(p) { }

    DEALERS_IDS_ENUM::_enumerated Order::getDealer() const {
        return dealer;
    };

    SIDES_TYPES_ENUM::_enumerated Order::getSide() const {
        return side;
    }

    COMMODITIES_TYPES_ENUM::_enumerated Order::getCommodity() const {
        return commodity;
    }

    Amount Order::getAmount() const {
        return amount;
    }

    Price Order::getPrice() const {
        return price;
    }

    void Order::reduce(const Amount a) {
        amount -= a;
    }
}