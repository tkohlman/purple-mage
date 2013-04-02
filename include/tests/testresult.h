/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <string>

enum TestStatus
{
        SUCCESS,
        FAILURE
};

class TestResult
{

public:

        TestResult(std::string testName, std::string errorMsg, TestStatus status);

        std::string testName;
        std::string errorMsg;
        TestStatus status;

};

#endif // TESTRESULT_H
