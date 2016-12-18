#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <iostream>
#include <exception>

class CustomException: public exception
{
    public:
        virtual const char* what() const throw()
};

#endif // CUSTOMEXCEPTION_H
