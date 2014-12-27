/*
 * FileSystemTest.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */
#include "FileSystemTest.h"
#include "MetaInfo.h"

using namespace std;
using namespace ML;

cute::suite make_suite_FileSystemTests() {
	cute::suite s;
	s.push_back(CUTE(test_file_system_example));
	return s;
}

void test_file_system_example() {
	FileSystem* fs = new FileSystem();

}
