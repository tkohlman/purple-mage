/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "unitfactory.h"
#include "testregistrar.h"
#include "unittest.h"

#include <iostream>

UnitFactory &UnitFactory::getInstance()
{
    static UnitFactory instance;
    return instance;
}

void UnitFactory::insert(const UnitTestTemplate &testTemplate)
{
    factoryMap.insert(testTemplate);
}

void UnitFactory::registerAll(TestRegistrar *registrar)
{
    FactoryMap::iterator iter = factoryMap.begin();
    while(iter != factoryMap.end())
    {
        std::cout << iter->first << std::endl;
        iter->second()->register_all(registrar);
        ++iter;
    }
}

void UnitFactory::clear()
{
    factoryMap.clear();
}
