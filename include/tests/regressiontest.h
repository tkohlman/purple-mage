/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef REGRESSIONTEST_H
#define REGRESSIONTEST_H

#include "assertionexception.h"
#include "testregistrar.h"

#include <map>
#include <string>
#include <iostream>

#define REGRESSIONTEST(t) class t; static regression_proxy p(#t, create< t >);

class RegressionTest
{

public:

    virtual void register_all(TestRegistrar *registrar) = 0;
};

template <class ConcreteRegressionTest>
RegressionTest *create()
{
    return new ConcreteRegressionTest();
}

// typedef to make it easier to set up our factory
typedef RegressionTest *maker_t();

// our global factory
extern std::map< std::string, maker_t *,
                 std::less<std::string> > &regression_factory();

inline void assert_equal();

inline void assert_equal(int i, int j)
{
    if (i != j)
    {
        AssertionException e;
        throw e;
    }
}

extern "C"
{
    class regression_proxy
    {
    public:
       regression_proxy(std::string testName, RegressionTest *(*f)())
       {
          // register the maker with the factory
          std::cout << "Creating regression test: " << testName << std::endl;
          regression_factory().insert(std::pair<std::string, maker_t*>(testName, f));
       }
    };
}

#endif // REGRESSIONTEST_H
