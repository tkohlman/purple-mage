/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef UNITTEST_H
#define UNITTEST_H

#include "assertionexception.h"
#include "testregistrar.h"

#include <map>
#include <string>
#include <iostream>
using namespace std;

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

// typedef to make it easier to set up our factory
typedef UnitTest *maker_t();

// our global factory
extern map< string, maker_t *, less<string> > &unit_factory();

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
       proxy(string testName, UnitTest *(*f)())
       {
          // register the maker with the factory
          cout << "Creating test: " << testName << endl;
          unit_factory().insert( pair<string, maker_t*>(testName, f));
       }
    };
}

#endif // UNITTEST_H
