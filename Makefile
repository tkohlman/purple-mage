#
# Created by gmakemake (Ubuntu Dec 29 2011) on Wed Feb 20 13:58:39 2013
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.s) -o $@ $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

AS =		as
CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.s = $(AS) $(ASFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm 
CCLIBFLAGS =	-ldl
########## End of default flags


CPP_FILES =	AssertionException.cpp DriveUnit.cpp QuitCommand.cpp RegressionSuiteA.cpp RegressionTestDriver.cpp TestA.cpp TestB.cpp TestResult.cpp UnitFunction.cpp main.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	AssertionException.h Command.h DriveUnit.h Observer.h QuitCommand.h RegressionSuiteA.h RegressionTest.h RegressionTestDriver.h Subject.h TestA.h TestB.h TestRegistrar.h TestResult.h UnitFunction.h UnitTest.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	AssertionException.o DriveUnit.o QuitCommand.o RegressionSuiteA.o RegressionTestDriver.o TestA.o TestB.o TestResult.o UnitFunction.o 

#
# Main targets
#

all:	main 

main:	main.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o main main.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

AssertionException.o:	AssertionException.h
DriveUnit.o:	AssertionException.h DriveUnit.h Observer.h Subject.h TestRegistrar.h TestResult.h UnitFunction.h UnitTest.h
QuitCommand.o:	Command.h QuitCommand.h
RegressionSuiteA.o:	AssertionException.h RegressionSuiteA.h RegressionTest.h TestRegistrar.h
RegressionTestDriver.o:	AssertionException.h Observer.h RegressionTest.h RegressionTestDriver.h Subject.h TestRegistrar.h TestResult.h UnitFunction.h
TestA.o:	AssertionException.h TestA.h TestRegistrar.h UnitTest.h
TestB.o:	AssertionException.h TestB.h TestRegistrar.h UnitTest.h
TestResult.o:	TestResult.h
UnitFunction.o:	TestResult.h UnitFunction.h
main.o:	

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) main.o core

realclean:        clean
	-/bin/rm -f main 
