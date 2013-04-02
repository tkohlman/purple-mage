/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "regressiontestdriver.h"

#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

// our global regression_factory()
std::map<std::string, maker_t *, std::less<std::string> > &regression_factory()
{
    static std::map<std::string, maker_t *, std::less<std::string> > *fact =
        new std::map<std::string, maker_t *, std::less<std::string> >();
    return *fact;
}

RegressionTestDriver::RegressionTestDriver()
{
    results = new std::vector<TestResult*>();
}

const std::vector< UnitFunction* > &RegressionTestDriver::getFunctions() const
{
    return functions;
}

void RegressionTestDriver::load(std::string solib)
{
    unload();

    // names
    void *dlib;

    printf("Loading shared object: %s\n", solib.c_str());
    dlib = dlopen(solib.c_str(), RTLD_NOW);

    if(dlib == NULL)
    {
        std::cerr << dlerror() << std::endl;
        exit(-1);
    }
    // add the handle to our list
    dl_list.insert(dl_list.end(), dlib);
    dlib = NULL;

    std::map<std::string, maker_t *, std::less<std::string> >::iterator fitr;
    for(fitr = regression_factory().begin(); fitr != regression_factory().end(); fitr++)
    {
        std::cout << fitr->first << std::endl;
        RegressionTest *test = fitr->second();
        test->register_all(this);
    }
}

void RegressionTestDriver::unload()
{
    // close all the dynamic libs we opened
    std::list<void *>::iterator itr;
    for(itr = dl_list.begin(); itr != dl_list.end(); itr++)
    {
        dlclose(*itr);
        *itr = NULL;
    }
    dl_list.clear();
    regression_factory().clear();
    functions.clear();
}

void RegressionTestDriver::execute()
{
    results->clear();
    std::cout << "Executing all unit tests..." << std::endl;
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
    std::cout << "Success rate: " << (double)success/results->size() << std::endl;
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
