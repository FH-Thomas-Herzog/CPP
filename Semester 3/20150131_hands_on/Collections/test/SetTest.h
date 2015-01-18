/*
 * SetTest.h
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */

#ifndef SETTEST_H_
#define SETTEST_H_

#include "cute.h"
#include "../Set.h"


cute::suite makeSuite();

// #########################################################
// Add, Append, Prepend tests
// #########################################################
void test_add_multpile_values();

void test_append_multpile_values();

void test_prepend_multpile_values();

// #########################################################
// Remove tests
// #########################################################
void test_remove_not_found();

void test_remove_empty();

void test_remove();

// #########################################################
// Intersect
// #########################################################
void test_intersect_null_source();

void test_intersect_empty_source();

void test_intersect_empty_result();

void test_intersect();

#endif /* SETTEST_H_ */
