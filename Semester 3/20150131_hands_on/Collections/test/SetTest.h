/*
 * SetTest.h
 * This is the Set Test specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */

#ifndef SETTEST_H_
#define SETTEST_H_

#include "cute.h"
#include "../Set.h"


cute::suite makeSetTestSuite();

// #########################################################
// Add, Append, Prepend tests
// #########################################################
void test_set_add_multpile_values();

void test_set_append_multpile_values();

void test_set_prepend_multpile_values();

// #########################################################
// Remove tests
// #########################################################
void test_set_remove_not_found();

void test_set_remove_empty();

void test_set_remove();

// #########################################################
// Intersect tests
// #########################################################
void test_set_intersect_null_source();

void test_set_intersect_empty_source();

void test_set_intersect_empty_result();

void test_set_intersect();

// #########################################################
// union tests
// #########################################################
void test_set_union_null_source();

void test_set_union_empty_source();

void test_set_union_duplicates();

void test_set_union();

// #########################################################
// complement tests
// #########################################################
void test_set_complement_null_source();

void test_set_complement_empty_source();

void test_set_complement_duplicates();

void test_set_complement();

#endif /* SETTEST_H_ */
