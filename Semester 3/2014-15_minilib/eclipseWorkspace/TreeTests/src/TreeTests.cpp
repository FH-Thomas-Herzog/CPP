#include "cute.h"
#include "TreeTests.h"

void thisIsATreeTestsTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_TreeTests(){
	cute::suite s;
	s.push_back(CUTE(thisIsATreeTestsTest));
	return s;
}



