/*
 * TreeTests.h
 * This is the specification for the tree tests.
 *
 *  Created on: Dec 23, 2014
 *      Author: Thomas Herzog
 */
#ifndef TREETESTS_H_
#define TREETESTS_H_

#include "cute.h"
#include <ostream>
#include <string>
#include "../Tree.h"
#include "../Node.h"
#include "../IntNode.h"

/**
 * This function puts he test function of this specification into
 * the given test suite which gets invoked by the test handler
 *
 * @param
 * 		s: the pointer to the suite where to add the test function references (is a vector)
 */
void make_suite_TreeTests(cute::suite* s);

////////////////////////////////////////////////////////////
// insertChild                                            //
////////////////////////////////////////////////////////////
void test_insertChild_null_parent();

void test_insertChild_null_child();

void test_insertChild_unmanaged_parent();

void test_insertChild_unmanaged_child();

////////////////////////////////////////////////////////////
// clear                                                  //
////////////////////////////////////////////////////////////
void test_clear();

////////////////////////////////////////////////////////////
// deleteElements                                         //
////////////////////////////////////////////////////////////
void test_deleteElements();

////////////////////////////////////////////////////////////
// deleteSubtree                                          //
////////////////////////////////////////////////////////////
void test_deleteSubtree_root();

void test_deleteSubtree_child();

void test_deleteSubtree_sibling();

////////////////////////////////////////////////////////////
// Examples and operators                                 //
////////////////////////////////////////////////////////////
void test_tree_example();

////////////////////////////////////////////////////////////
// print tree                                             //
////////////////////////////////////////////////////////////
void test_print_example();

////////////////////////////////////////////////////////////
// constructor and assign operator                        //
////////////////////////////////////////////////////////////
void test_copy_constructor();

void test_assign_operator();

#endif /* TREETESTS_H_ */
