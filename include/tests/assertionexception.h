#ifndef ASSERTIONEXCEPTION_H
#define ASSERTIONEXCEPTION_H

#include <exception>

class AssertionException : public std::exception
{

public:

        virtual const char *what() const throw();

};

#endif // ASSERTIONEXCEPTION_H
