/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef REGRESSIONTEST_H
#define REGRESSIONTEST_H

#include "testregistrar.h"
#include "dynamicfactory.h"

#include <string>
#include <iostream>

#define REGRESSIONTEST(t) class t; static regression_proxy p(#t, create< t >);

class RegressionTest
{

public:

    virtual void register_all(TestRegistrar *registrar) = 0;

    static void assert_equal(int i, int j);
};

template <class ConcreteRegressionTest>
RegressionTest *create()
{
    return new ConcreteRegressionTest();
}

extern "C"
{
    class regression_proxy
    {
    public:
        regression_proxy(std::string testName, RegressionTest *(*f)())
        {
            std::cout << "Creating regression test: " << testName << std::endl;
            DynamicFactory<RegressionTest>::getInstance().insert(
                DynamicFactory<RegressionTest>::DynamicTypeTemplate(testName,
                    f));
        }
    };
}

#endif // REGRESSIONTEST_H
