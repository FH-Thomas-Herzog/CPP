/*
 * hashtableTests.hpp
 * This header file specifies the test for the hashtable implementation
 *
 *  Created on: Apr 3, 2015
 *      Author: Thomas Herzog
 */

#ifndef HASHTABLETESTS_HPP_
#define HASHTABLETESTS_HPP_

#include <cute.h>
#include "../hashtable.hpp"

cute::suite createTestSuite();

//#####################################################
// hashtable tests
//#####################################################
void test_insert_new();
void test_insert_duplicate();


void test_erease_existing();

void test_erease_not_existing();

void test_contains_true();

void test_contains_false();

void test_clear_empty();

void test_clear_full();

void test_increase_load_factor();

void test_decrease_load_factor();

void test_equal_operator_same_instance();

void test_equal_operator_different_instance_true();

void test_equal_operator_different_instance_false();

#endif /* HASHTABLETESTS_HPP_ */
