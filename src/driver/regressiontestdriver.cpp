/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "regressiontestdriver.h"
#include "dynamicfactory.h"

#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

RegressionTestDriver::RegressionTestDriver()
{
    results = new std::vector<TestResult*>();
    DynamicFactory<RegressionTest>::getInstance().registerAll(this);
}

const std::vector< UnitFunction* > &RegressionTestDriver::getFunctions() const
{
    return functions;
}

void RegressionTestDriver::load(std::string solib)
{
    unload();

    void *dlib;

    printf("Loading shared object: %s\n", solib.c_str());
    dlib = dlopen(solib.c_str(), RTLD_NOW);

    if(dlib == NULL)
    {
        std::cerr << dlerror() << std::endl;
        exit(-1);
    }

    dl_list.insert(dl_list.end(), dlib);
    dlib = NULL;

    DynamicFactory<RegressionTest>::getInstance().registerAll(this);
}

void RegressionTestDriver::unload()
{
    std::list<void *>::iterator itr;
    for(itr = dl_list.begin(); itr != dl_list.end(); itr++)
    {
        dlclose(*itr);
        *itr = NULL;
    }
    dl_list.clear();
    DynamicFactory<RegressionTest>::getInstance().clear();
    functions.clear();
}

void RegressionTestDriver::execute()
{
    results->clear();
    std::cout << "Executing all regression tests..." << std::endl;
    std::vector< UnitFunction* >::iterator f_iter;

    success = failure = 0;

    for (f_iter = functions.begin(); f_iter != functions.end(); ++f_iter)
    {
        TestResult *r = (*f_iter)->execute();
        results->push_back(r);

        if (r->status == SUCCESS)
        {
            ++success;
        }
        else
        {
            ++failure;
        }

        sleep(1);
    }

    std::cout << success << " of " << results->size() << " tests passed" << std::endl;

    if (results->size() > 0)
    {
        std::cout << "Success rate: " << (double)success/results->size()
            << std::endl;
    }
}

void RegressionTestDriver::add_test(RegressionTest *unit)
{
    tests.push_back(unit);
}

void RegressionTestDriver::register_f(std::string suiteName, std::string testName, void (*f)())
{
    std::cout << "Registering function " << testName << " in suite " <<
        suiteName << std::endl;
    UnitFunction *func = new UnitFunction(suiteName, testName, f);
    functions.push_back(func);
}

void RegressionTestDriver::registerObserver(Observer *observer)
{
    observers.push_back(observer);
}

void RegressionTestDriver::unregisterObserver(Observer *observer)
{
    std::vector< Observer* >::iterator iter = observers.begin();

    for (; iter != observers.end(); ++iter)
    {
        if (observer == *iter)
        {
            iter = observers.erase(iter);
        }
    }
}

void RegressionTestDriver::notifyObservers()
{
    std::vector< Observer* >::iterator iter = observers.begin();

    for (; iter != observers.end(); ++iter)
    {
        (*iter)->notify();
    }
}
