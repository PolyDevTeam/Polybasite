#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <exception>

class Error : public std::exception {
public:
    Error();

    virtual const char* what() const throw();
    virtual ~Error();
};

#endif /* __ERROR_HPP__ */
