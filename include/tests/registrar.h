/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <string>

class Registrar
{

public:

    virtual void registerMethod(std::string className, std::string methodName,
        void (*methodPtr)()) = 0;

};

#endif // REGISTRAR_H
