#pragma once

#include <vector>
#include <string>
#include <boost/preprocessor/seq/enum.hpp>
#include <enum.h>


namespace cms {

    #define DEALERS_IDS (DB)(JPM)(UBS)(RBC)(BARX)(MS)(CITI)(BOFA)(RBS)(HSBC)
    BETTER_ENUM(DEALERS_IDS_ENUM, int, BOOST_PP_SEQ_ENUM(DEALERS_IDS))


    class Dealer {
    public:

        static bool isDealer(const std::string& id);

    };
}