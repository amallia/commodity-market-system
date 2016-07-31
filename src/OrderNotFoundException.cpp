#include "OrderNotFoundException.h"

OrderNotFoundException::OrderNotFoundException(const std::string &message) : message(message) {
}

OrderNotFoundException::~OrderNotFoundException() throw() {
}

const char *OrderNotFoundException::what() const throw() {
    return message.c_str();
}