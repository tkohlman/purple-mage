#ifndef TESTB_H
#define TESTB_H

#include "UnitTest.h"

UNITTEST(TestB);

class TestB : public UnitTest
{

public:

        virtual void register_all(TestRegistrar *registrar);

private:

        static void test5();
        static void test6();
        static void test7();
        static void test8();

};

#endif // TESTB_H
