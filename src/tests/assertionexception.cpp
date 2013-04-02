/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "assertionexception.h"

const char *AssertionException::what() const throw()
{
    return "Assertion failed.";
}
