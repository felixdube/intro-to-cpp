all: testytest

testytest:
	$ g++ -std=c++11 -g prioritiesTest.cpp prioritiesStudent.cpp priorities.h

gradygrade:
	$ g++ -std=c++11 -o gradygrade prioritiesGrading.cpp prioritiesStudent.cpp priorities.h

clean: 
	rm -rf *.o testytest gradygrade
