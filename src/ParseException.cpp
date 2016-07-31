#include "ParseException.h"

ParseException::ParseException(const std::string &message) : message(message) {
}

ParseException::~ParseException() throw() {
}

const char *ParseException::what() const throw() {
    return message.c_str();
}