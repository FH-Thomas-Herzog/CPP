/*
 * BagTest.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */
#include "BagTest.h"
#include "MLString.h"

using namespace cute;
using namespace ML;
using namespace std;

suite makeBagTestSuite() {
	suite setTestSuite;
	setTestSuite.push_back(CUTE(test_bag_add_multpile_values));
	setTestSuite.push_back(CUTE(test_bag_append_multpile_values));
	setTestSuite.push_back(CUTE(test_bag_prepend_multpile_values));

	setTestSuite.push_back(CUTE(test_bag_remove_not_found));
	setTestSuite.push_back(CUTE(test_bag_remove_empty));
	setTestSuite.push_back(CUTE(test_bag_remove));

	setTestSuite.push_back(CUTE(test_bag_intersect_null_source));
	setTestSuite.push_back(CUTE(test_bag_intersect_empty_source));
	setTestSuite.push_back(CUTE(test_bag_intersect_empty_result));
	setTestSuite.push_back(CUTE(test_bag_intersect));

	setTestSuite.push_back(CUTE(test_bag_union_null_source));
	setTestSuite.push_back(CUTE(test_bag_union_empty_source));
	setTestSuite.push_back(CUTE(test_bag_union_duplicates));
	setTestSuite.push_back(CUTE(test_bag_union));

	setTestSuite.push_back(CUTE(test_bag_complement_null_source));
	setTestSuite.push_back(CUTE(test_bag_complement_empty_source));
	setTestSuite.push_back(CUTE(test_bag_complement_duplicates));
	setTestSuite.push_back(CUTE(test_bag_complement));

	return setTestSuite;
}

// #########################################################
// Add, Append, Prepend tests
// #########################################################
void test_bag_add_multpile_values() {
	Bag* bag = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	bag->Add(val1);
	bag->Add(val2);
	bag->Add(val3);
	bag->Add(val4);
	/* Add duplicates */
	bag->Add(val1);
	bag->Add(val2);

	cout << *bag << endl << flush;

	ASSERT_EQUAL(6, bag->Size());

	delete bag;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();

}

void test_bag_append_multpile_values() {

}

void test_bag_prepend_multpile_values() {

}

// #########################################################
// Remove tests
// #########################################################
void test_bag_remove_not_found() {

}

void test_bag_remove_empty() {

}

void test_bag_remove() {

}

// #########################################################
// Intersect tests
// #########################################################
void test_bag_intersect_null_source() {

}

void test_bag_intersect_empty_source() {

}

void test_bag_intersect_empty_result() {

}

void test_bag_intersect() {

}

// #########################################################
// union tests
// #########################################################
void test_bag_union_null_source() {

}

void test_bag_union_empty_source() {

}

void test_bag_union_duplicates() {

}

void test_bag_union() {

}

// #########################################################
// complement tests
// #########################################################
void test_bag_complement_null_source() {

}

void test_bag_complement_empty_source() {

}

void test_bag_complement_duplicates() {

}

void test_bag_complement() {

}
