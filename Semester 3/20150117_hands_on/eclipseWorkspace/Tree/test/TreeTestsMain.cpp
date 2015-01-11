#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "TreeTests.h"
#include "FileSystemTest.h"

using namespace cute;

static void runSuite(int argc, char const *argv[]) {
	suite s;
	xml_file_opener xmlfile(argc, argv);
	xml_listener<ide_listener<> > lis(xmlfile.out);

	//s = make_suite_TreeTests();
	//makeRunner(lis, argc, argv)(s, "TreeTests");

	s = make_suite_FileSystemTests();
	makeRunner(lis, argc, argv)(s, "FileSystemTests");
}

int main(int argc, char const *argv[]) {
	runSuite(argc, argv);
}

