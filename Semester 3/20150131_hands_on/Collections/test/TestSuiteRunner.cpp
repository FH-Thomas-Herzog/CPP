/*
 * main.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: cchet
 */
#include "SetTest.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

using namespace std;
using namespace ML;
using namespace cute;

static void runSuite(int argc, char const *argv[]) {
	suite s;
	xml_file_opener xmlfile(argc, argv);
	xml_listener<ide_listener<> > lis(xmlfile.out);

	s = makeSuite();
	makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runSuite(argc, argv);
}
