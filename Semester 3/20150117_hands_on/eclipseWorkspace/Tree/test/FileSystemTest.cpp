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
	s.push_back(CUTE(test_mkdir_invalid_path));
	s.push_back(CUTE(test_mkdir_path_contain_files));
	s.push_back(CUTE(test_mkdir_valid));

	s.push_back(CUTE(test_touch_invalid_path));
	s.push_back(CUTE(test_touch_path_contain_files));
	s.push_back(CUTE(test_touch_valid_new));
	s.push_back(CUTE(test_touch_valid_existing));
	return s;
}

////////////////////////////////////////////////////////////
// mkdir tests                                            //
////////////////////////////////////////////////////////////
void test_mkdir_invalid_path() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("NOT_EXISTING/Downloads", "NEW_FOLDER");

	cout << *fs << endl;

	delete fs;

	WriteMetaInfo(cout);
}

void test_mkdir_path_contain_files() {

}

void test_mkdir_valid() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "root");
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->mkdir("home/cchet", "Downloads");
	fs->mkdir("home/cchet/Downloads", "eclipse-stuff");

	cout << *fs << endl;

	delete fs;

	WriteMetaInfo(cout);
}

////////////////////////////////////////////////////////////
// touch tests                                            //
////////////////////////////////////////////////////////////
void test_touch_invalid_path() {

	FileSystem* fs = new FileSystem();
	fs->touch("home", "testfile");

	cout << *fs << endl;

	delete fs;

	WriteMetaInfo(cout);
}

void test_touch_path_contain_files() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "root");
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->touch("home", "PART_OF_PATH");
	fs->mkdir("home/PART_OF_PATH/cchet", "Documents");

	cout << *fs << endl;

	delete fs;

	WriteMetaInfo(cout);
}

void test_touch_valid_new() {

	FileSystem* fs = new FileSystem();
	fs->touch("", "f1");
	fs->touch("", "f2");
	fs->touch("", "f3");

	delete fs;

	WriteMetaInfo(cout);
}

void test_touch_valid_existing() {

	FileSystem* fs = new FileSystem();
	fs->touch("", "f1");
	fs->touch("", "f1");

	delete fs;

	WriteMetaInfo(cout);
}
////////////////////////////////////////////////////////////
// rm tests                                               //
////////////////////////////////////////////////////////////
void test_rm_invalid_path() {

}

void test_rm_path_contain_files() {

}

void test_rm_not_found() {

}
void test_rm_directory() {

}

void test_rm_valid() {

}
