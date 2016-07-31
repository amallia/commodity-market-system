#pragma once

#include <exception>
#include <string>

class ParseException : public std::exception {
public:

    ParseException(const std::string &message);

    virtual const char *what() const throw();

    virtual ~ParseException() throw();

private:
    std::string message;
};

