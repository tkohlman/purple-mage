/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "driveunit.h"
#include "dynamicfactory.h"

#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

DriveUnit::DriveUnit()
{
    results = new std::vector<TestResult*>();
    DynamicFactory<UnitTest>::getInstance().registerAll(this);
}

const std::vector< UnitFunction* > &DriveUnit::getFunctions() const
{
    return functions;
}

void DriveUnit::load(std::string solib)
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

    DynamicFactory<UnitTest>::getInstance().registerAll(this);
}

void DriveUnit::unload()
{
    // close all the dynamic libs we opened
    std::list<void *>::iterator itr;
    for(itr = dl_list.begin(); itr != dl_list.end(); itr++)
    {
        dlclose(*itr);
        *itr = NULL;
    }
    dl_list.clear();
    DynamicFactory<UnitTest>::getInstance().clear();
    functions.clear();
}

void DriveUnit::execute()
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

    std::cout << success << " of " << results->size() << " tests passed"
            << std::endl;

    if (results->size() > 0)
    {

        std::cout << "Success rate: " << (double)success/results->size()
            << std::endl;
    }
}

void DriveUnit::add_unit(UnitTest *unit)
{
    tests.push_back(unit);
}

void DriveUnit::registerMethod(std::string className, std::string methodName,
                               void (*methodPtr)())
{
    std::cout << "Registering method " << methodName << " in class " <<
        className << std::endl;
    UnitFunction *func = new UnitFunction(className, methodName, methodPtr);
    functions.push_back(func);
}

void DriveUnit::registerObserver(Observer *observer)
{
    observers.push_back(observer);
}

void DriveUnit::unregisterObserver(Observer *observer)
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

void DriveUnit::notifyObservers()
{
    std::vector< Observer* >::iterator iter = observers.begin();

    for (; iter != observers.end(); ++iter)
    {
        (*iter)->notify();
    }
}
