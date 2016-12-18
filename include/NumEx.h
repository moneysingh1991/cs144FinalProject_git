#ifndef NUMEX_H
#define NUMEX_H

#include <exception>
class NumEx:public std::exception
{
   virtual const char* what() const throw();
};

#endif // NUMEX_H
