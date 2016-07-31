#pragma once

#include <boost/shared_ptr.hpp>

#include "Dealer.h"
#include "Side.h"
#include "Commodity.h"


namespace cms {

    typedef unsigned int OrderID;
    typedef int Amount;
    typedef double Price;

    class Order {

    private:
        DEALERS_IDS_ENUM::_enumerated dealer;
        SIDES_TYPES_ENUM::_enumerated side;
        COMMODITIES_TYPES_ENUM::_enumerated commodity;
        Amount amount;
        Price price;


    public:
        Order();

        Order(DEALERS_IDS_ENUM::_enumerated d, SIDES_TYPES_ENUM::_enumerated s,
              COMMODITIES_TYPES_ENUM::_enumerated commodity, Amount a, Price p);

        DEALERS_IDS_ENUM::_enumerated getDealer() const;

        SIDES_TYPES_ENUM::_enumerated getSide() const;

        COMMODITIES_TYPES_ENUM::_enumerated getCommodity() const;

        Amount getAmount() const;

        Price getPrice() const;

        void reduce(const Amount a);
    };
}