#pragma once
#include <boost/optional.hpp>

#include "Command.h"
#include "Dealer.h"
#include "Commodity.h"

namespace cms {

    class ListCommand : public Command {
        boost::optional<COMMODITIES_TYPES_ENUM::_enumerated> commodity;
        boost::optional<DEALERS_IDS_ENUM::_enumerated> ofDealer;

    public:
        ListCommand(DEALERS_IDS_ENUM::_enumerated d,  boost::optional<COMMODITIES_TYPES_ENUM> c, boost::optional<DEALERS_IDS_ENUM> od);
        std::string execute() const;
        boost::optional<COMMODITIES_TYPES_ENUM::_enumerated> getCommodity() const;
        boost::optional<DEALERS_IDS_ENUM::_enumerated> getOfDealer() const;


    };
}