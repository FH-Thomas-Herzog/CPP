/*
 * T9Tests.cpp
 * This source file contains the tests for the T9Converter.
 *
 *  Created on: Mar 15, 2015
 *      Author: Thomas Herzog
 */
#include <iostream>
#include <stdlib.h>
#include <cute.h>
#include "T9Tests.h"

using namespace std;
using namespace cute;
using namespace std::tr1;

/**
 * Global variable because no state is hold by the instance
 * and the dictonary load takes some time
 */
static T9Converter* t9;
static auto printStrings = ([](const string& s) {
	cout << ">"<< s << endl << flush;
});

suite buildSuite() {
	suite testSuite;
	testSuite.push_back(CUTE(initTests));

	testSuite.push_back(CUTE(test_w2n_invalid_char));
	testSuite.push_back(CUTE(test_w2n));

	testSuite.push_back(CUTE(test_n2s_invalid_digit));
	testSuite.push_back(CUTE(test_n2s));

	testSuite.push_back(CUTE(test_n2w_invalid_digit));
	testSuite.push_back(CUTE(test_n2w));

	testSuite.push_back(CUTE(test_n2wl_invalid_digit));
	testSuite.push_back(CUTE(test_n2wl));

	testSuite.push_back(CUTE(test_n2pw_invalid_digit));
	testSuite.push_back(CUTE(test_n2pw));

	testSuite.push_back(CUTE(test_n2psw_invalid_digit));
	testSuite.push_back(CUTE(test_n2psw));

	testSuite.push_back(CUTE(cleanupTests));

	return testSuite;
} /* buildSuite */

void initTests() {
	cout << "Initializing T9Converter instance..." << endl << flush;
	t9 = new T9Converter("de_neu.dic", "wiki.txt");
	cout << "finished" << endl << flush;
} /* initTests */

void cleanupTests() {
	delete t9;
} /* cleanupTests */

// ############################################################
// word2Number tests
// ############################################################
void test_w2n_invalid_char() {
	cout << endl << "word2Number(\"?\")" << endl << flush;
	ASSERT_EQUAL(-1, t9->word2Number("?"));

	cout << "word2Number(\"#\")" << endl << flush;
	ASSERT_EQUAL(-1, (long )t9->word2Number("#"));

	cout << "word2Number(\".\")" << endl << flush;
	ASSERT_EQUAL(-1, (long )t9->word2Number("."));
} /* test_w2n_invalid_char */

void test_w2n() {
	long long result;
	cout << endl << "word2Number(\"kiss\")" << endl << flush;
	result = t9->word2Number("kiss");
	cout << "result: " << result << endl << endl << flush;
	ASSERT_EQUAL(5477, result);
} /* test_w2n */

// ############################################################
// number2strings tests
// ############################################################
void test_n2s_invalid_digit() {
	cout << endl << "number2Strings(0)" << endl << flush;
	t9->number2Strings(0);
	cout << endl << "number2Strings(1)" << endl << flush;
	t9->number2Strings(1);
} /*test_n2s_invalid_digit */

void test_n2s() {
	unordered_set<string> result;
	cout << endl << "number2Strings(\"5477\")" << endl << flush;
	result = t9->number2Strings(5477);
	cout << "Resulting words: " << result.size() << endl << flush;
	for_each(result.begin(), result.end(), printStrings);
} /*test_n2s */

// ############################################################
// number2words tests
// ############################################################
void test_n2w_invalid_digit() {
	cout << endl << "number2Words(54771)" << endl << flush;
	t9->number2Words(54770);
	cout << endl << "number2Words(54770)" << endl << flush;
	t9->number2Words(54771);
} /* test_n2w_invalid_digit */

void test_n2w() {
	unordered_set<string> result;
	cout << endl << "number2Words(\"42556\")" << endl << flush;
	result = t9->number2Words(42556);
	cout << "Resulting words: " << result.size() << endl << flush;
	for_each(result.begin(), result.end(), printStrings);
} /* test_n2w */

// ############################################################
// number2wordsByLength tests
// ############################################################
void test_n2wl_invalid_digit() {
	cout << endl << "number2WordsByLength(54771)" << endl << flush;
	t9->number2WordsByLength(54770);
	cout << endl << "number2WordsByLength(54770)" << endl << flush;
	t9->number2WordsByLength(54771);
} /* test_n2wl_invalid_digit */

void test_n2wl() {
	unordered_set<string> result;
	cout << endl << "number2WordsByLength(\"42556\")" << endl << flush;
	result = t9->number2WordsByLength(42556);
	cout << "Resulting words: " << result.size() << endl << flush;
	for_each(result.begin(), result.end(), printStrings);
} /*test_n2wl */

// ############################################################
// numberPrefix2Words tests
// ############################################################
void test_n2pw_invalid_digit() {
	cout << endl << "numberPrefix2Words(54771)" << endl << flush;
	t9->numberPrefix2Words(54770);
	cout << endl << "numberPrefix2Words(54770)" << endl << flush;
	t9->numberPrefix2Words(54771);
} /* test_n2pw_invalid_digit */

void test_n2pw() {
	unordered_set<string> result;
	cout << endl << "numberPrefix2Words(\"42556\")" << endl << flush;
	result = t9->numberPrefix2Words(42556);
	cout << "Resulting words: " << result.size() << endl << flush;
	for_each(result.begin(), result.end(), printStrings);
} /* test_n2pw */

// ############################################################
// numberPrefix2sortedWords tests
// ############################################################
void test_n2psw_invalid_digit() {
	cout << endl << "numberPrefix2sortedWords(54771)" << endl << flush;
	t9->numberPrefix2sortedWords(54770);
	cout << endl << "numberPrefix2sortedWords(54770)" << endl << flush;
	t9->numberPrefix2sortedWords(54771);
} /* test_n2psw_invalid_digit */

void test_n2psw() {
	vector<string> result;
	cout << endl << "numberPrefix2sortedWords(\"42556\")" << endl << flush;
	result = t9->numberPrefix2sortedWords(42556);
	cout << "Resulting words: " << result.size() << endl << flush;
	for_each(result.begin(), result.end(), printStrings);
} /* test_n2psw */
