#include "CustomException.h"
#include <iostream>
#include <exception>

using namespace std;

const char* CustomException::what() const throw()
{
    return "Invalid Input caught";
}
