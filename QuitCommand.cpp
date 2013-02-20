
#include "QuitCommand.h"

#include <iostream>
#include <stdlib.h>
using namespace std;

void QuitCommand::execute()
{
    cout << "Quitting..." << endl;
    exit(EXIT_SUCCESS);
}
