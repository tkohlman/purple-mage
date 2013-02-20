

#include "RegressionTestDriver.h"

#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

// our global regression_factory()
map<string, maker_t *, less<string> > &regression_factory()
{
    static map<string,maker_t *, less<string> > *fact = new map<string, maker_t *, less<string> >();
    return *fact;
}

RegressionTestDriver::RegressionTestDriver()
{
    results = new vector<TestResult*>();
}

const vector< UnitFunction* > &RegressionTestDriver::getFunctions() const
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
        cerr << dlerror() << endl;
        exit(-1);
    }
    // add the handle to our list
    dl_list.insert(dl_list.end(), dlib);
    dlib = NULL;

    map<string, maker_t *, less<string> >::iterator fitr;
    for(fitr = regression_factory().begin(); fitr != regression_factory().end(); fitr++)
    {
        cout << fitr->first << endl;
        RegressionTest *test = fitr->second();
        test->register_all(this);
    }
}

void RegressionTestDriver::unload()
{
    // close all the dynamic libs we opened
    list<void *>::iterator itr;
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
    cout << "Executing all unit tests..." << endl;
    vector< UnitFunction* >::iterator f_iter;

    success = failure = 0;
    int total = functions.size();

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

    cout << success << " of " << results->size() << " tests passed" << endl;
    cout << "Success rate: " << (double)success/results->size() << endl;
}

void RegressionTestDriver::add_test(RegressionTest *unit)
{
    tests.push_back(unit);
}

void RegressionTestDriver::register_f(std::string suiteName, std::string testName, void (*f)())
{
    cout << "Registering function " << testName << " in suite " << suiteName << endl;
    UnitFunction *func = new UnitFunction(suiteName, testName, f);
    functions.push_back(func);
}

void RegressionTestDriver::registerObserver(Observer *observer)
{
    observers.push_back(observer);
}

void RegressionTestDriver::unregisterObserver(Observer *observer)
{
    vector< Observer* >::iterator iter = observers.begin();

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
    vector< Observer* >::iterator iter = observers.begin();

    for (; iter != observers.end(); ++iter)
    {
        (*iter)->notify();
    }
}
