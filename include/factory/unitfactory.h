/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef UNITFACTORY_H
#define UNITFACTORY_H

#include <map>
#include <string>

class UnitTest;
class TestRegistrar;

typedef UnitTest *UnitTestCtor();
typedef std::map<std::string, UnitTestCtor *, std::less<std::string> > UnitFactoryMap;
typedef std::pair<std::string, UnitTestCtor *> UnitTestTemplate;

class UnitFactory
{
public:

    static UnitFactory &getInstance();

    void insert(const UnitTestTemplate &testTemplate);

    void registerAll(TestRegistrar *registrar);

    void clear();

private:

    // Application of Singleton Pattern
    UnitFactory() {};
    UnitFactory(const UnitFactory &other);      // Unimplemented
    void operator=(const UnitFactory &other);   // Unimplemented

    UnitFactoryMap factoryMap;
};

#endif // UNITFACTORY_H
