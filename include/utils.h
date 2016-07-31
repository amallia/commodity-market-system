#pragma once

#include <string>
#include <boost/lexical_cast.hpp>

namespace cms {

    /*
     * Functions used check and convert strings to number.
     */

    int toInt(const std::string &string);

    double toDouble(const std::string &string);

    bool isInteger(const std::string &string);

    bool isDouble(const std::string &string);

}