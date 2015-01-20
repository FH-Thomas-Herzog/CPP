/*
 * main.cpp
 * This is the main for all of the test suites.
 *
 *  Created on: Jan 17, 2015
 *      Author: Thomas Herzog
 */
#include "SetTest.h"
#include "BagTest.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

using namespace std;
using namespace ML;
using namespace cute;

static void runSuite(int argc, char const *argv[]) {
	suite setTestSuite, bagTestSuite;
	xml_file_opener xmlfile(argc, argv);
	xml_listener<ide_listener<> > lis(xmlfile.out);

	setTestSuite = makeSetTestSuite();
	bagTestSuite = makeBagTestSuite();
	setTestSuite.insert(setTestSuite.end(), bagTestSuite.begin(),
			bagTestSuite.end());
	makeRunner(lis, argc, argv)(setTestSuite, "AllTests");


	WriteMetaInfo();
}

int main(int argc, char const *argv[]) {
	runSuite(argc, argv);
}
