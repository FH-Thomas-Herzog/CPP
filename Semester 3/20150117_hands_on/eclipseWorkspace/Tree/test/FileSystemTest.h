/*
 * FileSystemTest.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FILESYSTEMTEST_H_
#define FILESYSTEMTEST_H_

#include "cute.h"
#include <ostream>
#include <string>
#include "../FileSystem.h"
#include "../File.h"
#include "../FSNode.h"

cute::suite make_suite_FileSystemTests();

////////////////////////////////////////////////////////////
// mkdir tests                                            //
////////////////////////////////////////////////////////////
void test_mkdir_invalid_path();

void test_mkdir_path_contain_files();

void test_mkdir_valid();

////////////////////////////////////////////////////////////
// touch tests                                            //
////////////////////////////////////////////////////////////
void test_touch_invalid_path();

void test_touch_path_contain_files();

void test_touch_valid_new();

void test_touch_valid_existing();

////////////////////////////////////////////////////////////
// rm tests                                               //
////////////////////////////////////////////////////////////
void test_rm_invalid_path();

void test_rm_path_contain_files();

void test_rm_not_found();

void test_rm_directory();

void test_rm_valid();

////////////////////////////////////////////////////////////
// rmdir tests                                            //
////////////////////////////////////////////////////////////
void test_rmdir_invalid_path();

void test_rmdir_path_contain_files();

void test_rmdir_not_found();

void test_rmdir_file();

void test_rmdir_valid();

////////////////////////////////////////////////////////////
// ls tests                                               //
////////////////////////////////////////////////////////////
void test_ls();

////////////////////////////////////////////////////////////
// complex example tests                                  //
////////////////////////////////////////////////////////////
void test_complex_example();

#endif /* FILESYSTEMTEST_H_ */
