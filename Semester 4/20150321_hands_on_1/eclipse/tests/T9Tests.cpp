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
static long long T9_SHORT_STRING = 786583;
static long long T9_LONG_STRING = 428787266537;
static string SHORT_STRING = "Punkte";
static string LONG_STRING = "Hauptsammler";

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
}

void initTests() {
	cout << "Initializing T9Converter instance..." << endl << flush;
	t9 = new T9Converter("de_neu.dic", "wiki.txt");
	cout << "finished" << endl << flush;
}

void cleanupTests() {
	delete t9;
}

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
}

void test_w2n() {
	long long result;
	cout << endl << "word2Number(\"" + LONG_STRING + "\")" << endl << flush;
	result = t9->word2Number(LONG_STRING);
	cout << "result: " << result << endl << endl << flush;
	ASSERT_EQUAL(T9_LONG_STRING, result);

	cout << "word2Number(\"" + SHORT_STRING + "\")" << endl << flush;
	result = t9->word2Number(SHORT_STRING);
	cout << "result: " << result << endl << flush;
	ASSERT_EQUAL(T9_SHORT_STRING, result);
}

// ############################################################
// number2strings tests
// ############################################################
void test_n2s_invalid_digit() {
	cout << endl << "number2Strings(0)" << endl << flush;
	t9->number2Strings(0);
	cout << endl << "number2Strings(1)" << endl << flush;
	t9->number2Strings(1);
}

void test_n2s() {
	unordered_set<string> result;
	cout << endl << "number2Strings("<< T9_SHORT_STRING <<")" << endl << flush;
	result = t9->number2Strings(T9_SHORT_STRING);
	for_each(result.begin(), result.end(), printStrings);

	result.erase(result.begin(), result.end());
	// ATTENTION: Extremely inefficient permutation calculation
	cout << endl << "number2Strings("<< T9_LONG_STRING <<")" << endl << flush;
//	result = t9->number2Strings(T9_LONG_STRING);
	for_each(result.begin(), result.end(), printStrings);
}
// ############################################################
// number2words tests
// ############################################################
void test_n2w_invalid_digit() {
	cout << endl << "number2Words(54771)" << endl << flush;
	t9->number2Words(54770);
	cout << endl << "number2Words(54770)" << endl << flush;
	t9->number2Words(54771);
}

void test_n2w() {
	unordered_set<string> result;
	cout << endl << "number2Words("<< T9_SHORT_STRING <<")" << endl << flush;
	result = t9->number2Words(T9_SHORT_STRING);
	for_each(result.begin(), result.end(), printStrings);

	result.erase(result.begin(), result.end());
	cout << endl << "number2Words("<< T9_LONG_STRING <<")" << endl << flush;
	result = t9->number2Words(T9_LONG_STRING);
	for_each(result.begin(), result.end(), printStrings);
}

// ############################################################
// number2wordsByLength tests
// ############################################################
void test_n2wl_invalid_digit() {
	cout << endl << "number2WordsByLength(54771)" << endl << flush;
	t9->number2WordsByLength(54770);
	cout << endl << "number2WordsByLength(54770)" << endl << flush;
	t9->number2WordsByLength(54771);
}

void test_n2wl() {
	unordered_set<string> result;
	cout << endl << "number2WordsByLength("<< T9_SHORT_STRING <<")" << endl << flush;
	result = t9->number2WordsByLength(T9_SHORT_STRING);
	for_each(result.begin(), result.end(), printStrings);

	result.erase(result.begin(), result.end());
	cout << endl << "number2WordsByLength("<< T9_LONG_STRING <<")" << endl << flush;
	result = t9->number2WordsByLength(T9_LONG_STRING);
	for_each(result.begin(), result.end(), printStrings);
}

// ############################################################
// numberPrefix2Words tests
// ############################################################
void test_n2pw_invalid_digit() {
	cout << endl << "numberPrefix2Words(54771)" << endl << flush;
	t9->numberPrefix2Words(54770);
	cout << endl << "numberPrefix2Words(54770)" << endl << flush;
	t9->numberPrefix2Words(54771);
}

void test_n2pw() {
	unordered_set<string> result;
	cout << endl << "numberPrefix2Words("<< T9_SHORT_STRING <<")" << endl << flush;
	result = t9->numberPrefix2Words(T9_SHORT_STRING);
	for_each(result.begin(), result.end(), printStrings);

	result.erase(result.begin(), result.end());
	cout << endl << "numberPrefix2Words("<< T9_LONG_STRING <<")" << endl << flush;
	result = t9->number2WordsByLength(T9_LONG_STRING);
	for_each(result.begin(), result.end(), printStrings);
}

// ############################################################
// numberPrefix2sortedWords tests
// ############################################################
void test_n2psw_invalid_digit() {
	cout << endl << "numberPrefix2sortedWords(54771)" << endl << flush;
	t9->numberPrefix2sortedWords(54770);
	cout << endl << "numberPrefix2sortedWords(54770)" << endl << flush;
	t9->numberPrefix2sortedWords(54771);
}

void test_n2psw() {
	vector<string> result;
	cout << endl << "numberPrefix2sortedWords("<< T9_SHORT_STRING <<")" << endl << flush;
	result = t9->numberPrefix2sortedWords(T9_SHORT_STRING);
	for_each(result.begin(), result.end(), printStrings);

	result.erase(result.begin(), result.end());
	cout << endl << "numberPrefix2sortedWords("<< T9_LONG_STRING <<")" << endl << flush;
	result = t9->numberPrefix2sortedWords(T9_LONG_STRING);
	for_each(result.begin(), result.end(), printStrings);
}
