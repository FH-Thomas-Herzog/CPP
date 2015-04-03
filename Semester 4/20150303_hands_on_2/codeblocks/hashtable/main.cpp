/*
 * main.cpp
 * This is the main which invokes the tests.
 *
 *  Created on: Mar 27, 2015
 *      Author: Thomas Herzog
 */
#include "test/hashtableTests.hpp"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

using namespace std;
using namespace cute;

static void runSuite(int argc, char const *argv[]) {
	suite setTestSuite, bagTestSuite;
	xml_file_opener xmlfile(argc, argv);
	xml_listener<ide_listener<> > lis(xmlfile.out);

	setTestSuite = createTestSuite();
	makeRunner(lis, argc, argv)(setTestSuite, "AllTests");
} /* runSuite */

int main(int argc, char const *argv[]) {
	runSuite(argc, argv);
} /* main */
