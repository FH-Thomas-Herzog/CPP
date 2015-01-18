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
// Intersect tests
// #########################################################
void test_intersect_null_source();

void test_intersect_empty_source();

void test_intersect_empty_result();

void test_intersect();

// #########################################################
// union tests
// #########################################################
void test_union_null_source();

void test_union_empty_source();

void test_union_duplicates();

void test_union();

// #########################################################
// complement tests
// #########################################################
void test_complement_null_source();

void test_complement_empty_source();

void test_complement_duplicates();

void test_complement();

#endif /* SETTEST_H_ */
