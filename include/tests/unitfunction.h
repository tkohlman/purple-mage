/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef UNITFUNCTION_H
#define UNITFUNCTION_H

#include "testresult.h"
#include <string>
#include <iostream>

class UnitFunction
{

public:

    UnitFunction(std::string suiteName, std::string testName, void (*f)());

    TestResult *execute();
    std::string suiteName;
    std::string testName;

private:


    void (*function)();
};

#endif // UNITFUNCTION_H
