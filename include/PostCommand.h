#pragma once

#include "PostCommand.h"
#include "Command.h"
#include "Side.h"
#include "Commodity.h"
#include "Order.h"
namespace cms {
    class PostCommand : public Command {

    public:
        PostCommand(DEALERS_IDS_ENUM::_enumerated d,SIDES_TYPES_ENUM::_enumerated s, COMMODITIES_TYPES_ENUM::_enumerated c, Amount a, Price p);
        std::string execute() const;
        Amount getAmount() const;
        Price getPrice() const;
        SIDES_TYPES_ENUM::_enumerated getSide() const;
        COMMODITIES_TYPES_ENUM::_enumerated getCommodity() const;

    private:
        SIDES_TYPES_ENUM::_enumerated side;
        COMMODITIES_TYPES_ENUM::_enumerated commodity;
        Amount amount;
        Price price;
    };

}