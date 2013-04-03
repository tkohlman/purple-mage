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

typedef UnitTest *ctor_fptr();
typedef std::map<std::string, ctor_fptr *, std::less<std::string> > FactoryMap;
typedef std::pair<std::string, ctor_fptr *> UnitTestTemplate;

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

    FactoryMap factoryMap;
};

#endif // UNITFACTORY_H
