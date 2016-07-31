#include "Command.h"

namespace cms {

    Command::Command(DEALERS_IDS_ENUM::_enumerated d) {
        dealerID = d;
    }

    DEALERS_IDS_ENUM::_enumerated Command::getDealerID() const{
        return dealerID;
    }
    std::string const Command::order_info_string = "%1% %2% %3% %4% %5% %6%";
}