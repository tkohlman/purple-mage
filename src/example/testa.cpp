/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "testa.h"

void TestA::register_all(Registrar *registrar)
{
    registrar->registerMethod("TestA", "test1", &test1);
    registrar->registerMethod("TestA", "test2", &test2);
    registrar->registerMethod("TestA", "test3", &test3);
    registrar->registerMethod("TestA", "test4", &test4);
}

void TestA::test1()
{
    assert_equal(1, 1);
}

void TestA::test2()
{
    assert_equal(1, 2);
}

void TestA::test3()
{
    int i = 1 + 1;
    int j = 2;
    assert_equal(i, j);
}

void TestA::test4()
{
    assert_equal(0, 0);
}
