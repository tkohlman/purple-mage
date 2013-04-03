/*
 * Copyright (c) 2013 Thomas Kohlman
 * See license.txt for copying permission.
 */

#include "driveunit.h"
#include "regressiontestdriver.h"

#include <iostream>

int main( int argc, char **argv )
{
	std::cout << "purplemage v1.0" << std::endl;

	DriveUnit unitDriver;
	unitDriver.execute();

	RegressionTestDriver regressionTestDriver;
	regressionTestDriver.execute();
}
