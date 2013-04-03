/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef UNITTEST_H
#define UNITTEST_H

#include "assertionexception.h"
#include "testregistrar.h"
#include "unitfactory.h"

#include <map>
#include <string>
#include <iostream>

#define UNITTEST(t) class t; static proxy p(#t, create< t >);

class UnitTest
{

public:

    virtual void register_all(TestRegistrar *registrar) = 0;
};

template <class ConcreteUnitTest>
UnitTest *create()
{
    return new ConcreteUnitTest();
}

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
    class proxy
    {
    public:
       proxy(std::string testName, UnitTest *(*f)())
       {
          // register the ctor function pointer with the factory
          std::cout << "Creating test: " << testName << std::endl;
          UnitFactory::getInstance().insert(UnitTestTemplate(testName, f));
       }
    };
}

#endif // UNITTEST_H
