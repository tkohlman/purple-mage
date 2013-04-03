/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef REGRESSIONFACTORY_H
#define REGRESSIONFACTORY_H


#include <map>
#include <string>

class RegressionTest;
class TestRegistrar;

typedef RegressionTest *RegressionTestCtor();
typedef std::map<std::string, RegressionTestCtor *, std::less<std::string> > RegressionFactoryMap;
typedef std::pair<std::string, RegressionTestCtor *> RegressionTestTemplate;

class RegressionFactory
{
public:

    static RegressionFactory &getInstance();

    void insert(const RegressionTestTemplate &testTemplate);

    void registerAll(TestRegistrar *registrar);

    void clear();

private:

    // Application of Singleton Pattern
    RegressionFactory() {};
    RegressionFactory(const RegressionFactory &other);  // Unimplemented
    void operator=(const RegressionFactory &other);     // Unimplemented

    RegressionFactoryMap factoryMap;
};

#endif // REGRESSIONFACTORY_H
