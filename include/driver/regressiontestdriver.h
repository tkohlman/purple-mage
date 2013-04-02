/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

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

    const std::vector< UnitFunction* > &getFunctions() const;

private:

    std::vector< RegressionTest* > tests;

    std::vector< UnitFunction* > functions;

    std::vector< TestResult* > *results;

    std::vector< Observer* > observers;

    int success, failure;

    std::list<void *> dl_list; // list to hold handles for dynamic libs
};

#endif // REGRESSIONTESTDRIVER_H
