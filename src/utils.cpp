#include "utils.h"

namespace cms {

    template<typename Type>
    Type convertToType(const std::string &string) {
        return boost::lexical_cast<Type>(string);
    }

    int toInt(const std::string &string) {
        return convertToType<int>(string);
    }

    double toDouble(const std::string &string) {
        return convertToType<double>(string);
    }

    template<typename Type>
    bool isType(const std::string &string) {
        try {
            convertToType<Type>(string);
            return true;
        }
        catch (boost::bad_lexical_cast &e) {
            return false;
        }
    }

    bool isInteger(const std::string &string) {
        return isType<int>(string);
    }

    bool isDouble(const std::string &string) {
        return isType<double>(string);
    }
}