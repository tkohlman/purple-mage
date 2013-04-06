/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef UNITTEST_H
#define UNITTEST_H

#include "dynamicfactory.h"

#include <string>
#include <iostream>

#define UNITTEST(t) class t; static proxy p(#t, create< t >);

class Registrar;

class UnitTest
{

public:

    virtual void register_all(Registrar *registrar) = 0;

    static void assert_equal(int i, int j);
};

template <class ConcreteUnitTest>
UnitTest *create()
{
    return new ConcreteUnitTest();
}

extern "C"
{
    class proxy
    {
    public:
       proxy(std::string testName, UnitTest *(*f)())
       {
          // register the ctor function pointer with the factory
          std::cout << "Creating unit test: " << testName << std::endl;
          DynamicFactory<UnitTest>::getInstance().insert(
                DynamicFactory<UnitTest>::DynamicTypeTemplate(testName, f));
       }
    };
}

#endif // UNITTEST_H
