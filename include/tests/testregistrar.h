#ifndef TESTREGISTRAR_H
#define TESTREGISTRAR_H

#include <string>
using namespace std;

class TestRegistrar
{

public:

    virtual void register_f(std::string suiteName, std::string testName, void (*f)()) = 0;

};

#endif // TESTREGISTRAR_H