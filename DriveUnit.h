#ifndef DRIVEUNIT_H
#define DRIVEUNIT_H


#include "TestRegistrar.h"
#include "UnitTest.h"
#include "UnitFunction.h"
#include "Subject.h"

#include <vector>
#include <string>
#include <iostream>
#include <list>
using namespace std;

class DriveUnit : TestRegistrar, public Subject
{
public:

    DriveUnit();

    void load(std::string solib);
    void unload();
    void execute();
    void add_unit(UnitTest *unit);
    void register_f(std::string suiteName, std::string testName, void (*f)());

    void registerObserver(Observer *observer);
    void unregisterObserver(Observer *observer);
    void notifyObservers();

    const vector< UnitFunction* > &getFunctions() const;

private:

    vector< UnitTest* > tests;

    vector< UnitFunction* > functions;

    vector< TestResult* > *results;

    vector< Observer* > observers;

    int success, failure;

    list<void *> dl_list; // list to hold handles for dynamic libs
};

#endif // DRIVEUNIT_H