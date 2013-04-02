#ifndef UNITFUNCTION_H
#define UNITFUNCTION_H

#include "testresult.h"
#include <string>
#include <iostream>
using namespace std;

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
