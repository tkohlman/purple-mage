/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "testb.h"

void TestB::register_all(Registrar *registrar)
{
    registrar->registerMethod("TestB", "test5", &test5);
    registrar->registerMethod("TestB", "test6", &test6);
    registrar->registerMethod("TestB", "test7", &test7);
    registrar->registerMethod("TestB", "test8", &test8);
}

void TestB::test5()
{
    assert_equal(1, 1);
}

void TestB::test6()
{
    assert_equal(1, 2);
}

void TestB::test7()
{
    int i = 1 + 1;
    int j = 2;
    assert_equal(i, j);
}

void TestB::test8()
{
        assert_equal(0, 0);
}
