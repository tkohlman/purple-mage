/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef TESTA_H
#define TESTA_H

#include "unittest.h"

UNITTEST(TestA)

class TestA : public UnitTest
{

public:

        virtual void register_all(Registrar *registrar);

private:

        static void test1();
        static void test2();
        static void test3();
        static void test4();

};

#endif // TESTA_H
