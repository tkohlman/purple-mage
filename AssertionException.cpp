
#include "AssertionException.h"

const char *AssertionException::what() const throw()
{
    return "Assertion failed.";
}
