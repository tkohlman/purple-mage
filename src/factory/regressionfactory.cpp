/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */


#include "regressionfactory.h"
#include "testregistrar.h"
#include "regressiontest.h"

#include <iostream>

RegressionFactory &RegressionFactory::getInstance()
{
    static RegressionFactory instance;
    return instance;
}

void RegressionFactory::insert(const RegressionTestTemplate &testTemplate)
{
    factoryMap.insert(testTemplate);
}

void RegressionFactory::registerAll(TestRegistrar *registrar)
{
    RegressionFactoryMap::iterator iter = factoryMap.begin();
    while(iter != factoryMap.end())
    {
        std::cout << iter->first << std::endl;
        iter->second()->register_all(registrar);
        ++iter;
    }
}

void RegressionFactory::clear()
{
    factoryMap.clear();
}
