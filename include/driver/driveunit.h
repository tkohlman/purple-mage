/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef DRIVEUNIT_H
#define DRIVEUNIT_H


#include "registrar.h"
#include "unittest.h"
#include "unitfunction.h"
#include "subject.h"

#include <vector>
#include <string>
#include <iostream>
#include <list>

class DriveUnit : Registrar, public Subject
{
public:

    DriveUnit();

    void load(std::string solib);
    void unload();
    void execute();
    void add_unit(UnitTest *unit);
    void registerMethod(std::string className, std::string methodName,
                        void (*methodPtr)());

    void registerObserver(Observer *observer);
    void unregisterObserver(Observer *observer);
    void notifyObservers();

    const std::vector< UnitFunction* > &getFunctions() const;

private:

    std::vector< UnitTest* > tests;

    std::vector< UnitFunction* > functions;

    std::vector< TestResult* > *results;

    std::vector< Observer* > observers;

    int success, failure;

    std::list<void *> dl_list; // list to hold handles for dynamic libs
};

#endif // DRIVEUNIT_H
