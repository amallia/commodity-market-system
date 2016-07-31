#pragma once

#include <exception>
#include <string>

class OrderNotFoundException : public std::exception {
public:

    OrderNotFoundException(const std::string &message);
    virtual const char *what() const throw();
    virtual ~OrderNotFoundException() throw();

private:
    std::string message;
};

