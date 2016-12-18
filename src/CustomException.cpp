#include "CustomException.h"
#include <iostream>
#include <exception>

using namespace std;

virtual const char* CustomException::what()
{
    return "Invalid Input caught";
}
