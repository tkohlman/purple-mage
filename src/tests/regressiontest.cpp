/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "assertionexception.h"
#include "regressiontest.h"

void RegressionTest::assert_equal(int i, int j)
{
    if (i != j)
    {
        AssertionException e;
        throw e;
    }
}
