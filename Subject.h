#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Subject
{

public:

    virtual void registerObserver(Observer *observer) = 0;

    virtual void unregisterObserver(Observer *observer) = 0;

    virtual void notifyObservers() = 0;
};

#endif // SUBJECT_H