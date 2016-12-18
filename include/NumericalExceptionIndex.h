#ifndef NUMERICALEXCEPTIONINDEX_H
#define NUMERICALEXCEPTIONINDEX_H

#include <exception>
class NumericalExceptionIndex: public std::exception
{
    public:
        const char * what() const throw();
} numex;

#endif // NUMERICALEXCEPTIONINDEX_H
