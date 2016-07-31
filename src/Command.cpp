#include "Command.h"

namespace cms {

    Command::Command(DEALERS_IDS_ENUM::_enumerated d) {
        dealerID = d;
    }

    DEALERS_IDS_ENUM::_enumerated Command::getDealerID() const {
        return dealerID;
    }

    const std::string Command::order_info_string = "%1% %2% %3% %4% %5% %6%";
    const std::string Command::aggress_string = "%1% %2% %3% @ %4% FROM %5%";
    const std::string Command::post_string = "%1% %2% %3% %4% %5% %6% HAS BEEN POSTED";
    const std::string Command::revoke_string = "%1% HAS BEEN REVOKED";
    const std::string Command::filled_string = "%1% HAS BEEN FILLED";

}