#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "tests/T9Tests.h"

using namespace std;
using namespace cute;

static void runSuite(int argc, char const *argv[]) {
	suite setTestSuite, bagTestSuite;
	xml_file_opener xmlfile(argc, argv);
	xml_listener<ide_listener<> > lis(xmlfile.out);

	setTestSuite = buildSuite();
	makeRunner(lis, argc, argv)(setTestSuite, "AllTests");
}

int main(int argc, char const *argv[]) {
	runSuite(argc, argv);
}
