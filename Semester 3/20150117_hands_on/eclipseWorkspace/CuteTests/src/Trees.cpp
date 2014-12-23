#include "cute.h"
#include "Trees.h"

void thisIsATreesTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_Trees(){
	cute::suite s;
	s.push_back(CUTE(thisIsATreesTest));
	return s;
}



