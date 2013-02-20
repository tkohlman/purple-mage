
#include "TestA.h"

void TestA::register_all(TestRegistrar *registrar)
{
    registrar->register_f("TestA", "test1", &test1);
    registrar->register_f("TestA", "test2", &test2);
    registrar->register_f("TestA", "test3", &test3);
    registrar->register_f("TestA", "test4", &test4);
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
