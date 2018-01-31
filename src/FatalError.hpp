#ifndef __FATALERROR_HPP__
#define __FATALERROR_HPP__

#include "Error.hpp"

class FatalError : public Error {
    FatalError();
    virtual ~FatalError();
    virtual const char* what() const throw();
};

#endif /* __FATALERROR_HPP__ */
