#ifndef TESTA_H
#define TESTA_H

#include "unittest.h"

UNITTEST(TestA)

class TestA : public UnitTest
{

public:

        virtual void register_all(TestRegistrar *registrar);

private:

        static void test1();
        static void test2();
        static void test3();
        static void test4();

};

#endif // TESTA_H
