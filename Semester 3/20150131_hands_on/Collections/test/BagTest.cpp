/*
 * BagTest.cpp
 * This is the implementation of the Bag Test specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
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
	setTestSuite.push_back(CUTE(test_bag_union_nothing_todo));
	setTestSuite.push_back(CUTE(test_bag_union));

	setTestSuite.push_back(CUTE(test_bag_complement_null_source));
	setTestSuite.push_back(CUTE(test_bag_complement_empty_source));
	setTestSuite.push_back(CUTE(test_bag_complement_empty_result));
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
	Bag* bag = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	bag->Append(val1);
	bag->Append(val2);
	bag->Append(val3);
	bag->Append(val4);
	/* Add duplicates */
	bag->Append(val1);
	bag->Append(val2);

	cout << *bag << endl << flush;

	ASSERT_EQUAL(6, bag->Size());

	delete bag;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_bag_prepend_multpile_values() {
	Bag* bag = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	bag->Prepend(val1);
	bag->Prepend(val2);
	bag->Prepend(val3);
	bag->Prepend(val4);
	/* Add duplicates */
	bag->Prepend(val1);
	bag->Prepend(val2);

	cout << *bag << endl << flush;

	ASSERT_EQUAL(6, bag->Size());

	delete bag;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

// #########################################################
// Remove tests
// #########################################################
void test_bag_remove_not_found() {
	Bag* bag = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");

	bag->Prepend(val1);
	bag->Prepend(val2);

	cout << "Before Remove Target: " << endl << *bag << endl << endl << flush;
	bag->Remove(val3);
	cout << "After Remove Target: " << endl << *bag << endl << flush;

	ASSERT_EQUAL(2, bag->Size());

	delete bag;
	delete val1;
	delete val2;
	delete val3;

	WriteMetaInfo();
}

void test_bag_remove_empty() {
	Bag* bag = new Bag();
	String* val1 = new String("value 1");

	cout << "Before Remove Target: " << endl << *bag << endl << endl << flush;
	bag->Remove(val1);
	cout << "After Remove Target: " << endl << *bag << endl << flush;

	ASSERT_EQUAL(0, bag->Size());

	delete bag;
	delete val1;

	WriteMetaInfo();
}

void test_bag_remove() {
	Bag* bag = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	bag->Prepend(val1);
	bag->Prepend(val2);
	bag->Prepend(val3);
	bag->Prepend(val4);
	/* Add duplicates */
	bag->Prepend(val1);
	bag->Prepend(val2);

	cout << "Before Remove Target: " << endl << *bag << endl << endl << flush;
	bag->Remove(val1);
	bag->Remove(val1);
	bag->Remove(val2);
	bag->Remove(val2);
	bag->Remove(val3);
	cout << "After Remove Target: " << endl << *bag << endl << flush;

	ASSERT_EQUAL(1, bag->Size());

	delete bag;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

// #########################################################
// Intersect tests
// #########################################################
void test_bag_intersect_null_source() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	target->Prepend(val1);
	target->Prepend(val2);
	target->Prepend(val3);
	target->Prepend(val4);

	cout << "Before Intersect Target: " << endl << *target << endl << endl << flush;
	target->Intersect(nullptr);
	cout << "After Intersect Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(4, target->Size());

	delete target;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_bag_intersect_empty_source() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");

	target->Prepend(val1);
	target->Prepend(val2);
	target->Prepend(val3);
	target->Prepend(val4);

	Bag* source = new Bag();

	cout << "Before Intersect Source: " << endl << *source << endl << endl << flush;
	cout << "Before Intersect Target: " << endl << *target << endl << endl << flush;
	target->Intersect(source);
	cout << "After Intersect Source: " << endl << *source << endl << endl << flush;
	cout << "After Intersect Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(0, target->Size());
	ASSERT_EQUAL(0, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_bag_intersect_empty_result() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val2);

	Bag* source = new Bag();
	String* val3 = new String("value 3");
	String* val4 = new String("value 4");
	source->Prepend(val3);
	source->Prepend(val4);

	cout << "Before Intersect Source: " << endl << *source << endl << endl << flush;
	cout << "Before Intersect Target: " << endl << *target << endl << endl << flush;
	target->Intersect(source);
	cout << "After Intersect Source: " << endl << *source << endl << endl << flush;
	cout << "After Intersect Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(0, target->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_bag_intersect() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");
	String* val3 = new String("value 3");

	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val2);
	target->Prepend(val2);
	target->Prepend(val2);
	target->Prepend(val3);

	Bag* source = new Bag();
	String* val4 = new String("value 1");
	String* val5 = new String("value 2");
	source->Prepend(val4);
	source->Prepend(val5);
	source->Prepend(val5);
	source->Prepend(val5);
	source->Prepend(val5);
	source->Prepend(val5);
	source->Prepend(val5);

	cout << "Before Intersect Source: " << endl << *source << endl << endl << flush;
	cout << "Before Intersect Target: " << endl << *target << endl << endl << flush;
	target->Intersect(source);
	cout << "After Intersect Source: " << endl << *source << endl << endl << flush;
	cout << "After Intersect Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(4, target->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;
	delete val5;


	WriteMetaInfo();
}

// #########################################################
// union tests
// #########################################################
void test_bag_union_null_source() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val2);

	cout << "Before Union Target: " << endl << *target << endl << endl << flush;
	target->Union(nullptr);
	cout << "After Union Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(2, target->Size());

	delete target;
	delete val1;
	delete val2;

	WriteMetaInfo();
}

void test_bag_union_empty_source() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val2);

	Bag* source = new Bag();

	cout << "Before Union Source: " << endl << *source << endl << endl << flush;
	cout << "Before Union Target: " << endl << *target << endl << endl << flush;
	target->Union(source);
	cout << "After Union Source: " << endl << *source << endl << endl << flush;
	cout << "After Union Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(2, target->Size());
	ASSERT_EQUAL(0, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;

	WriteMetaInfo();
}


void test_bag_union_nothing_todo() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val2);
	target->Prepend(val2);

	Bag* source = new Bag();
	String* val3 = new String("value 1");
	String* val4 = new String("value 2");
	source->Prepend(val3);
	source->Prepend(val3);
	source->Prepend(val4);
	source->Prepend(val4);


	cout << "Before Union Source: " << endl << *source << endl << endl << flush;
	cout << "Before Union Target: " << endl << *target << endl << endl << flush;
	target->Union(source);
	cout << "After Union Source: " << endl << *source << endl << endl << flush;
	cout << "After Union Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(4, target->Size());
	ASSERT_EQUAL(4, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_bag_union() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val2);
	target->Prepend(val2);

	Bag* source = new Bag();
	String* val3 = new String("value 1");
	String* val4 = new String("value 2");
	String* val5 = new String("value 3");
	source->Prepend(val3);
	source->Prepend(val4);
	source->Prepend(val4);
	source->Prepend(val4);
	source->Prepend(val4);
	source->Prepend(val5);
	source->Prepend(val5);


	cout << "Before Union Source: " << endl << *source << endl << endl << flush;
	cout << "Before Union Target: " << endl << *target << endl << endl << flush;
	target->Union(source);
	cout << "After Union Source: " << endl << *source << endl << endl << flush;
	cout << "After Union Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(10, target->Size());
	ASSERT_EQUAL(7, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;
	delete val5;

	WriteMetaInfo();
}

// #########################################################
// complement tests
// #########################################################
void test_bag_complement_null_source() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val2);

	cout << "Before Complement Target: " << endl << *target << endl << endl << flush;
	target->Complement(nullptr);
	cout << "After Complement Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(2, target->Size());

	delete target;
	delete val1;
	delete val2;

	WriteMetaInfo();
}

void test_bag_complement_empty_source() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val2);

	Bag* source = new Bag();

	cout << "Before Complement Source: " << endl << *source << endl << endl << flush;
	cout << "Before Complement Target: " << endl << *target << endl << endl << flush;
	target->Complement(source);
	cout << "After Complement Source: " << endl << *source << endl << endl << flush;
	cout << "After Complement Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(2, target->Size());
	ASSERT_EQUAL(0, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;

	WriteMetaInfo();
}

void test_bag_complement_empty_result() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	target->Prepend(val1);
	target->Prepend(val2);

	Bag* source = new Bag();
	String* val3 = new String("value 1");
	String* val4 = new String("value 2");

	source->Prepend(val3);
	source->Prepend(val4);

	cout << "Before Complement Source: " << endl << *source << endl << endl << flush;
	cout << "Before Complement Target: " << endl << *target << endl << endl << flush;
	target->Complement(source);
	cout << "After Complement Source: " << endl << *source << endl << endl << flush;
	cout << "After Complement Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(0, target->Size());
	ASSERT_EQUAL(2, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}

void test_bag_complement() {
	Bag* target = new Bag();
	String* val1 = new String("value 1");
	String* val2 = new String("value 2");

	/* target has more than source */
	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val1);
	target->Prepend(val1);
	/* target has less than source */
	target->Prepend(val2);

	Bag* source = new Bag();
	String* val3 = new String("value 1");
	String* val4 = new String("value 2");

	source->Prepend(val3);
	source->Prepend(val3);
	source->Prepend(val3);
	source->Prepend(val4);
	source->Prepend(val4);

	cout << "Before Complement Source: " << endl << *source << endl << endl << flush;
	cout << "Before Complement Target: " << endl << *target << endl << endl << flush;
	target->Complement(source);
	cout << "After Complement Source: " << endl << *source << endl << endl << flush;
	cout << "After Complement Target: " << endl << *target << endl << flush;

	ASSERT_EQUAL(1, target->Size());
	ASSERT_EQUAL(5, source->Size());

	delete target;
	delete source;
	delete val1;
	delete val2;
	delete val3;
	delete val4;

	WriteMetaInfo();
}
