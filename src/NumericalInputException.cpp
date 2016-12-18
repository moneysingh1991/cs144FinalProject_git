#include "NumericalInputException.h"
#include <exception>

using namespace std;

const char* NumericalInputException::what() const throw()
{
    return "Invalid input detected. Expected a number.";
}
