/*
 * T9Tests.h
 * This header file specifies the tests for the T9Converter
 *
 *  Created on: Mar 15, 2015
 *      Author: Thomas Herzog
 */

#ifndef T9TESTS_H_
#define T9TESTS_H_

#include "cute.h"
#include "../T9Converter.h"

/**
 * prepares the suite by collection the test functions
 */
cute::suite buildSuite();

/**
 * Inits the tests by initializing the T9converter with the
 * dictonary, which takes some time.
 */
void initTests();

/**
 * Cleans the tests up
 */
void cleanupTests();

// ############################################################
// word2Number tests
// ############################################################
void test_w2n_invalid_char();

void test_w2n();

// ############################################################
// number2strings tests
// ############################################################
void test_n2s_invalid_digit();

void test_n2s();

// ############################################################
// number2words tests
// ############################################################
void test_n2w_invalid_digit();

void test_n2w();

// ############################################################
// number2wordsByLength tests
// ############################################################
void test_n2wl_invalid_digit();

void test_n2wl();

// ############################################################
// numberPrefix2Words tests
// ############################################################
void test_n2pw_invalid_digit();

void test_n2pw();

// ############################################################
// numberPrefix2sortedWords tests
// ############################################################
void test_n2psw_invalid_digit();

void test_n2psw();

#endif /* T9TESTS_H_ */
