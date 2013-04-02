/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

class Subject
{

public:

    virtual void registerObserver(Observer *observer) = 0;

    virtual void unregisterObserver(Observer *observer) = 0;

    virtual void notifyObservers() = 0;
};

#endif // SUBJECT_H
