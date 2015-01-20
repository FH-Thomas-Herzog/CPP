/*
 * BagTest.h
 * This is the Bag Test specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */
#ifndef BAGTEST_H_
#define BAGTEST_H_

#include "cute.h"
#include "../Bag.h"

cute::suite makeBagTestSuite();
// #########################################################
// Add, Append, Prepend tests
// #########################################################
void test_bag_add_multpile_values();

void test_bag_append_multpile_values();

void test_bag_prepend_multpile_values();

// #########################################################
// Remove tests
// #########################################################
void test_bag_remove_not_found();

void test_bag_remove_empty();

void test_bag_remove();

// #########################################################
// Intersect tests
// #########################################################
// #########################################################
// Intersect tests
// #########################################################
void test_bag_intersect_null_source();

void test_bag_intersect_empty_source();

void test_bag_intersect_empty_result();

void test_bag_intersect();

// #########################################################
// union tests
// #########################################################
void test_bag_union_null_source();

void test_bag_union_empty_source();

void test_bag_union_nothing_todo();

void test_bag_union();

// #########################################################
// complement tests
// #########################################################
void test_bag_complement_null_source();

void test_bag_complement_empty_source();

void test_bag_complement_empty_result();

void test_bag_complement();

#endif /* BAGTEST_H_ */
