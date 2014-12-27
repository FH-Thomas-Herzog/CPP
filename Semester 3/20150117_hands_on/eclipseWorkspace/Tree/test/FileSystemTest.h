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

void test_file_system_example();

#endif /* FILESYSTEMTEST_H_ */
