
#include "regressionsuitea.h"

void RegressionSuiteA::register_all(TestRegistrar *registrar)
{
    registrar->register_f("RegressionSuiteA", "regressionTest1", &regressionTest1);
    registrar->register_f("RegressionSuiteA", "regressionTest2", &regressionTest2);
    registrar->register_f("RegressionSuiteA", "regressionTest3", &regressionTest3);
    registrar->register_f("RegressionSuiteA", "regressionTest4", &regressionTest4);
}

void RegressionSuiteA::regressionTest1()
{
    assert_equal(1, 1);
}

void RegressionSuiteA::regressionTest2()
{
    assert_equal(1, 2);
}

void RegressionSuiteA::regressionTest3()
{
    int i = 1 + 1;
    int j = 2;
    assert_equal(i, j);
}

void RegressionSuiteA::regressionTest4()
{
    assert_equal(0, 0);
}
