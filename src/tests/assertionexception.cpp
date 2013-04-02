
#include "assertionexception.h"

const char *AssertionException::what() const throw()
{
    return "Assertion failed.";
}
