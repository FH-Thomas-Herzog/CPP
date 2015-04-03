/*
 * hashtableTests.cpp
 * This is the implementation of the specification hashtableTests.hpp
 *
 *  Created on: Apr 3, 2015
 *      Author: Thomas Herzog
 */
#include "hashtableTests.hpp"

using namespace std;
using namespace cute;

suite createTestSuite() {
	suite testSuite;
	testSuite.push_back(CUTE(test_insert_new));
	testSuite.push_back(CUTE(test_insert_duplicate));
	testSuite.push_back(CUTE(test_erease_existing));
	testSuite.push_back(CUTE(test_erease_not_existing));
	testSuite.push_back(CUTE(test_contains_true));
	testSuite.push_back(CUTE(test_contains_false));
	testSuite.push_back(CUTE(test_clear_empty));
	testSuite.push_back(CUTE(test_clear_full));
	testSuite.push_back(CUTE(test_increase_load_factor));
	testSuite.push_back(CUTE(test_decrease_load_factor));
	testSuite.push_back(CUTE(test_equal_operator_same_instance));
	testSuite.push_back(CUTE(test_equal_operator_different_instance_true));
	testSuite.push_back(CUTE(test_equal_operator_different_instance_false));
	return testSuite;
} /* createTestSuite */

static void printTable(
		hashtable<string, std::hash<string>, std::equal_to<string>> ht,
		string desc) {
	cout << "Hashtable content: " << desc << endl << "------------------------"
			<< endl << ht << endl << "------------------------" << endl;
} /* printTable */

//#####################################################
// hashtable tests
//#####################################################
void test_insert_new() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	printTable(ht, "before insert");

	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(string("C++"));

	printTable(ht, "after insert");

	ASSERT_EQUAL(3, ht.size());
} /* test_insert_new */

void test_insert_duplicate() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	printTable(ht, "before insert");

	ht.insert(string("Hello"));
	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(string("you"));
	ht.insert(string("C++"));
	ht.insert(string("C++"));

	printTable(ht, "after insert");

	ASSERT_EQUAL(3, ht.size());
} /* test_insert_duplicate */

void test_erease_existing() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	string s("C++");
	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(s);

	printTable(ht, "before erease");

	ht.erase(s);

	printTable(ht, "after erease");

	ASSERT_EQUAL(2, ht.size());
} /* test_erease_existing */

void test_erease_not_existing() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	string s("not-existing");
	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(string("C++"));

	printTable(ht, "before erease");

	ht.erase(s);

	printTable(ht, "after erease");

	ASSERT_EQUAL(3, ht.size());

} /* test_erease_not_existing */

void test_contains_true() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	string s("C++");
	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(s);

	printTable(ht, "");

	ASSERT_EQUAL(true, ht.contains(s));
} /* test_contains_true */

void test_contains_false() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	string s("not-existing");
	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(string("C++"));

	printTable(ht, "");

	ASSERT_EQUAL(false, ht.contains(s));
} /* test_contains_false */

void test_clear_empty() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	printTable(ht, "before clear");

	ht.clear();

	printTable(ht, "after clear");

	ASSERT_EQUAL(0, ht.size());
} /* test_clear_empty */

void test_clear_full() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	ht.insert(string("Hello"));
	ht.insert(string("you"));
	ht.insert(string("C++"));

	printTable(ht, "before clear");

	ht.clear();

	printTable(ht, "after clear");

	ASSERT_EQUAL(0, ht.size());
} /* test_clear_full */

void test_increase_load_factor() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	for (int i = 0; i < 20; i++) {
		stringstream ss;
		ss << "Element_" << i;
		ht.insert(ss.str());
	}

	ASSERT_EQUAL(33, ht.capacity());
} /* test_increase_load_factor */

void test_decrease_load_factor() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(30);

	for (int i = 0; i < 20; i++) {
		stringstream ss;
		ss << "Element_" << i;
		ht.insert(ss.str());
	}

	for (int i = 0; i < 20; ++i) {
		stringstream ss;
		ss << "Element_" << i;
		ht.erase(ss.str());
	}

	ASSERT_EQUAL(16, ht.capacity());

} /* test_decrease_load_factor */

void test_equal_operator_same_instance() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht(10);

	ht.insert(string("Hello"));

	ASSERT_EQUAL(true, ht == ht);
} /* test_equal_operator_same_instance */

void test_equal_operator_different_instance_true() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht1(10);
	hashtable<string, std::hash<string>, std::equal_to<string>> ht2(10);

	ht1.insert(string("Hello"));
	ht2.insert(string("Hello"));

	ASSERT_EQUAL(true, ht1 == ht2);
} /* test_equal_operator_different_instance_true */

void test_equal_operator_different_instance_false() {
	hashtable<string, std::hash<string>, std::equal_to<string>> ht1(10);
	hashtable<string, std::hash<string>, std::equal_to<string>> ht2(10);

	ht1.insert(string("Hello"));
	ht2.insert(string("You too"));

	ASSERT_EQUAL(false, ht1 == ht2);

} /* test_equal_operator_different_instance_false*/
