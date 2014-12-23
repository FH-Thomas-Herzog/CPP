/*
 * TreeTests.h
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#ifndef TREETESTS_H_
#define TREETESTS_H_

#include "cute.h"
#include <ostream>
#include <string>
#include "../Tree.h"
#include "../Node.h"

cute::suite make_suite_TreeTests();

void test_insertChild_null_parent();

void test_insertChild_null_child();

void test_insertChild_unmanaged_parent();

#endif /* TREETESTS_H_ */
