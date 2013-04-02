/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "testresult.h"

TestResult::TestResult(string testName, string errorMsg, TestStatus status):
        testName(testName), errorMsg(errorMsg), status(status)
{

}

