/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "unittest.h"
#include "assertionexception.h"

void UnitTest::assert_equal(int i, int j)
{
    if (i != j)
    {
        AssertionException e;
        throw e;
    }
}
