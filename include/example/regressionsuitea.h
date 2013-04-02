#ifndef REGRESSIONSUITEA_H
#define REGRESSIONSUITEA_H

#include "regressiontest.h"

//UNITTEST(TestA);

class RegressionSuiteA : public RegressionTest
{

public:

        virtual void register_all(TestRegistrar *registrar);

private:

        static void regressionTest1();
        static void regressionTest2();
        static void regressionTest3();
        static void regressionTest4();

};

#endif // REGRESSIONSUITEA_H
