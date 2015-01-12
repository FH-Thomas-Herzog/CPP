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

	s.push_back(CUTE(test_rm_invalid_path));
	s.push_back(CUTE(test_rm_path_contain_files));
	s.push_back(CUTE(test_rm_not_found));
	s.push_back(CUTE(test_rm_directory));
	s.push_back(CUTE(test_rm_valid));

	s.push_back(CUTE(test_rmdir_invalid_path));
	s.push_back(CUTE(test_rmdir_path_contain_files));
	s.push_back(CUTE(test_rmdir_not_found));
	s.push_back(CUTE(test_rmdir_file));
	s.push_back(CUTE(test_rmdir_valid));

	s.push_back(CUTE(test_ls));

	s.push_back(CUTE(test_complex_example));

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
	FileSystem* fs = new FileSystem();
	fs->touch("", "f1");

	fs->rm("home", "f1");

	cout << *fs << endl << flush;

	delete fs;

	WriteMetaInfo(cout);
}

void test_rm_path_contain_files() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->touch("home/cchet", "f1");
	fs->touch("home/cchet/Documents", "f2");

	fs->rm("home/cchet/f1/Documents", "f2");

	delete fs;

	WriteMetaInfo(cout);
}

void test_rm_not_found() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->touch("home/cchet", "f1");

	fs->rm("home/cchet", "f2");

	delete fs;

	WriteMetaInfo(cout);
}

void test_rm_directory() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->touch("home/cchet", "f1");

	fs->rm("home", "cchet");

	delete fs;

	WriteMetaInfo(cout);
}

void test_rm_valid() {
	FileSystem* fs = new FileSystem();
	fs->touch("", "f1");
	fs->touch("", "f2");

	fs->rm("", "f1");

	cout << *fs << endl << flush;

	delete fs;

	WriteMetaInfo(cout);
}

////////////////////////////////////////////////////////////
// rmdir tests                                            //
////////////////////////////////////////////////////////////
void test_rmdir_invalid_path() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->mkdir("home/cchet/Documents", "Receipts");

	fs->rmdir("home/other/Documents", "Receipts");

	delete fs;

	WriteMetaInfo(cout);
}

void test_rmdir_path_contain_files() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->touch("home/cchet", "f1");
	fs->mkdir("home/cchet/Documents", "Receipts");

	fs->rmdir("home/cchet/f1/Documents", "Receipts");

	delete fs;

	WriteMetaInfo(cout);
}

void test_rmdir_not_found() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->mkdir("home/cchet/Documents", "Receipts");

	fs->rmdir("home/cchet/Documents", "blabla");

	delete fs;

	WriteMetaInfo(cout);

}

void test_rmdir_file() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->touch("home/cchet", "f1");
	fs->mkdir("home/cchet/Documents", "Receipts");

	fs->rmdir("home/cchet/", "f1");

	delete fs;

	WriteMetaInfo(cout);
}

void test_rmdir_valid() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->touch("home/cchet", "f1");
	fs->touch("home/cchet", "f2");
	fs->touch("home/cchet", "f3");
	fs->touch("home/cchet", "f4");

	fs->rmdir("home", "cchet");

	cout << *fs << endl << flush;

	delete fs;

	WriteMetaInfo(cout);
}

////////////////////////////////////////////////////////////
// ls tests                                               //
////////////////////////////////////////////////////////////
void test_ls() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "home");
	fs->mkdir("home", "cchet");
	fs->mkdir("home/cchet", "Documents");
	fs->touch("home/cchet", "f1");
	fs->touch("home/cchet", "f2");
	fs->touch("home/cchet", "f3");
	fs->touch("home/cchet", "f4");

	fs->ls();
}

////////////////////////////////////////////////////////////
// complex example tests                                  //
////////////////////////////////////////////////////////////
void test_complex_example() {
	FileSystem* fs = new FileSystem();
	fs->mkdir("", "root");
	fs->touch("root", "ReadMe.txt");
	fs->mkdir("root", "bin");
	fs->touch("root/bin", "a.exe");
	fs->touch("root/bin", "b.exe");
	//fs->ls();
	fs->rm("root/bin", "a.exe");
	fs->rmdir("", "root");
	//fs->ls();
	fs->rm("root/bin", "b.exe");
	fs->rmdir("", "root/bin");
	fs->rm("root", "ReadMe.txt");
	fs->rmdir("", "root");
	fs->ls();

	delete fs;

	WriteMetaInfo(cout);
}