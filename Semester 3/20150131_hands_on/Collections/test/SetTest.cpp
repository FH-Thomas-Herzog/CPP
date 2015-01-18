/*
 * SetTest.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */
#include "SetTest.h"
#include "MLString.h"

using namespace cute;
using namespace ML;
using namespace std;

suite makeSuite() {
	suite setTestSuite;
	setTestSuite.push_back(CUTE(test_add_multpile_values));
	setTestSuite.push_back(CUTE(test_append_multpile_values));
	setTestSuite.push_back(CUTE(test_prepend_multpile_values));

	setTestSuite.push_back(CUTE(test_remove_not_found));
	setTestSuite.push_back(CUTE(test_remove_empty));
	setTestSuite.push_back(CUTE(test_remove));

	setTestSuite.push_back(CUTE(test_intersect_null_source));
	setTestSuite.push_back(CUTE(test_intersect_empty_source));
	setTestSuite.push_back(CUTE(test_intersect_empty_result));
	setTestSuite.push_back(CUTE(test_intersect));

	return setTestSuite;
}

// #########################################################
// Add, Append, Prepend tests
// #########################################################
void test_add_multpile_values() {
	Set* set = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	set->Add(val1);
	set->Add(val2);
	set->Add(val3);
	set->Add(val4);
	/* Add duplicates */
	set->Add(val1);
	set->Add(val2);

	cout << *set << endl << flush;

	ASSERT_EQUAL(4, set->Size());

	delete set;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_append_multpile_values() {
	Set* set = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	set->Append(val1);
	set->Append(val2);
	set->Append(val3);
	set->Append(val4);
	/* Append duplicates */
	set->Append(val1);
	set->Append(val2);

	cout << *set << endl << flush;

	ASSERT_EQUAL(4, set->Size());

	delete set;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_prepend_multpile_values() {
	Set* set = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	set->Prepend(val1);
	set->Prepend(val2);
	set->Prepend(val3);
	set->Prepend(val4);
	/* Prepend duplicates */
	set->Prepend(val1);
	set->Prepend(val2);

	cout << *set << endl << flush;

	ASSERT_EQUAL(4, set->Size());

	delete set;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

// #########################################################
// Remove tests
// #########################################################
void test_remove_not_found() {
	Set* set = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");

	set->Add(val1);
	set->Add(val2);

	cout << "Before remove:" << endl << *set << endl << endl << flush;

	set->Remove(val3);

	cout << "After remove:" << endl << *set << endl << flush;

	ASSERT_EQUAL(2, set->Size());

	delete set;
	delete val1;
	delete val2;
	delete val3;

	WriteMetaInfo();
}

void test_remove_empty() {
	Set* set = new Set();
	String* val3 = new String("value 3");

	cout << "Before remove:" << endl << *set << endl << endl << flush;

	set->Remove(val3);

	cout << "After remove:" << endl << *set << endl << flush;

	ASSERT_EQUAL(0, set->Size());

	delete set;
	delete val3;

	WriteMetaInfo();
}

void test_remove() {
	Set* set = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	set->Add(val1);
	set->Add(val2);

	cout << "Before remove:" << endl << *set << endl << endl << flush;

	set->Remove(val2);

	cout << "After remove:" << endl << *set << endl << flush;

	ASSERT_EQUAL(1, set->Size());

	delete set;
	delete val1;
	delete val2;

	WriteMetaInfo();
}

// #########################################################
// Intersect
// #########################################################
void test_intersect_null_source() {
	Set* target = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	target->Add(val1);
	target->Add(val2);

	target->Intersect(nullptr);

	ASSERT_EQUAL(2, target->Size());

	delete target;
	delete val1;
	delete val2;

	WriteMetaInfo();
}

void test_intersect_empty_source() {
	Set* target = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	target->Add(val1);
	target->Add(val2);

	Set* source = new Set();

	target->Intersect(source);

	ASSERT_EQUAL(0, target->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;

	WriteMetaInfo();
}

void test_intersect_empty_result() {
	Set* target = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	target->Add(val1);
	target->Add(val2);

	Set* source = new Set();
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");
	source->Add(val3);
	source->Add(val4);

	cout << "Target:" << endl << *target << endl << endl << flush;
	cout << "Source:" << endl << *source << endl << endl << flush;

	target->Intersect(source);

	cout << "After Intersect Target:" << endl << *target << endl << endl << flush;

	ASSERT_EQUAL(0, target->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_intersect() {

	Set* target = new Set();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	target->Add(val1);
	target->Add(val2);

	Set* source = new Set();
	String* val3 = new String("value 1");
	String* val4 = new String("value 4");
	source->Add(val3);
	source->Add(val4);

	cout << "Target:" << endl << *target << endl << endl << flush;
	cout << "Source:" << endl << *source << endl << endl << flush;

	target->Intersect(source);

	cout << "AFter intersect Target:" << endl << *target << endl << endl << flush;

	ASSERT_EQUAL(1, target->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}
