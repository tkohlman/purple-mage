#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <string>
using namespace std;

enum TestStatus
{
        SUCCESS,
        FAILURE
};

class TestResult
{

public:

        TestResult(string testName, string errorMsg, TestStatus status);

        string testName;
        string errorMsg;
        TestStatus status;

};

#endif // TESTRESULT_H