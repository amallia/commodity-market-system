#pragma once

#include <map>
#include <boost/thread/mutex.hpp>
#include "Order.h"

namespace cms {

    /*
     * Functions used to manage the orders database.
     */

    namespace orderRepository {

        Order& findOne(OrderID i);

        OrderID add(Order o);

        const std::map<OrderID, Order*>& list();

        const std::map<OrderID, Order*>& list(COMMODITIES_TYPES_ENUM::_enumerated c);

        const std::map<OrderID, Order*>& list(COMMODITIES_TYPES_ENUM::_enumerated c, DEALERS_IDS_ENUM::_enumerated d);

        void remove(OrderID i);


    };
}