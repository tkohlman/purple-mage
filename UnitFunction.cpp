
#include "UnitFunction.h"

UnitFunction::UnitFunction(std::string suiteName, std::string testName, void (*f)()):
        suiteName(suiteName), testName(testName), function(f)
{
}

TestResult *UnitFunction::execute()
{
    try
    {
        cout << "Running test: " << testName << "...";
        function();
        TestResult *result = new TestResult(testName, "", SUCCESS);
        cout << "pass" << endl;
        return result;
    }
    catch (exception &e)
    {
        //cout << e.what() << endl;
        cout << "fail" << endl;
        TestResult *result = new TestResult(testName, e.what(), FAILURE);
        return result;
    }
}
