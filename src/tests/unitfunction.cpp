/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "unitfunction.h"

UnitFunction::UnitFunction(std::string suiteName, std::string testName,
                           void (*f)()):
        suiteName(suiteName), testName(testName), function(f)
{
}

TestResult *UnitFunction::execute()
{
    try
    {
        std::cout << "Running test: " << testName << "...";
        function();
        TestResult *result = new TestResult(testName, "", SUCCESS);
        std::cout << "pass" << std::endl;
        return result;
    }
    catch (std::exception &e)
    {
        //cout << e.what() << endl;
        std::cout << "fail" << std::endl;
        TestResult *result = new TestResult(testName, e.what(), FAILURE);
        return result;
    }
}
