#ifndef NUMERICALINPUTEXCEPTION_H
#define NUMERICALINPUTEXCEPTION_H

#include <iostream>
#include "exception.h"

class NumericalInputException: public std::exception
{
    public:
        virtual const char* what() const throw();
} NumericalInputException;

#endif // NUMERICALINPUTEXCEPTION_H
