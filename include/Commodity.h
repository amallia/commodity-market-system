#pragma once

#include <vector>
#include <string>
#include <boost/preprocessor/seq/enum.hpp>
#include <enum.h>

namespace cms {

    #define COMMODITIES_TYPES (GOLD)(SILV)(PORK)(OIL)(RICE)
    BETTER_ENUM(COMMODITIES_TYPES_ENUM, int, BOOST_PP_SEQ_ENUM(COMMODITIES_TYPES))

    class Commodity {
    public:

        static bool isCommodity(const std::string& id);

    };
}