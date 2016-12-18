#include "NumericalExceptionIndex.h"

const char* NumericalExceptionIndex::what() const throw(){
    return "Expected number. Invalid input.";
}
