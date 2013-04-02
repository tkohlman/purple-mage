#ifndef REGRESSIONTESTDRIVER_H
#define REGRESSIONTESTDRIVER_H

#include "testregistrar.h"
#include "regressiontest.h"
#include "unitfunction.h"
#include "subject.h"

#include <vector>
#include <string>
#include <iostream>
#include <list>
using namespace std;

class RegressionTestDriver : TestRegistrar
{
public:

    RegressionTestDriver();

    void load(std::string solib);
    void unload();
    void execute();
    void add_test(RegressionTest *unit);
    void register_f(std::string suiteName, std::string testName, void (*f)());

    void registerObserver(Observer *observer);
    void unregisterObserver(Observer *observer);
    void notifyObservers();

    const vector< UnitFunction* > &getFunctions() const;

private:

    vector< RegressionTest* > tests;

    vector< UnitFunction* > functions;

    vector< TestResult* > *results;

    vector< Observer* > observers;

    int success, failure;

    list<void *> dl_list; // list to hold handles for dynamic libs
};

#endif // REGRESSIONTESTDRIVER_H
