#include <algorithm>
#include "Dealer.h"

namespace cms {

    bool Dealer::isDealer(const std::string& id) {
        if (std::find(DEALERS_IDS_ENUM::_names().begin(), DEALERS_IDS_ENUM::_names().end(), id) != DEALERS_IDS_ENUM::_names().end())
            return true;
        return false;
    }
}