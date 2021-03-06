/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef TESTB_H
#define TESTB_H

#include "unittest.h"

UNITTEST(TestB)

class TestB : public UnitTest
{

public:

        virtual void register_all(Registrar *registrar);

private:

        static void test5();
        static void test6();
        static void test7();
        static void test8();

};

#endif // TESTB_H
