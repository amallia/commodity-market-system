#include <algorithm>
#include "Commodity.h"

namespace cms {



    bool Commodity::isCommodity(const std::string& id) {
        if (std::find(COMMODITIES_TYPES_ENUM::_names().begin(), COMMODITIES_TYPES_ENUM::_names().end(), id) != COMMODITIES_TYPES_ENUM::_names().end())
            return true;
        return false;
    }
}