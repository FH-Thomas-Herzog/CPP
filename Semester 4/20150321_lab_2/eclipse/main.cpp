#include <iostream>
#include <set>
#include <iterator> // ostream_iterator
#include <algorithm> // for_each
#include <memory> // unique_ptr, shared_ptr

#include "person.h"
#include "student.h"
#include "scoped_ptr.hpp"
#include "counted_ptr.hpp"
// #include "ext_counted_ptr.hpp"

using namespace std;

/**
 * Here we see the slicing effect which causes memory leaks.
 */
static void static_collection_test() {
	set<person> person_set;
	person_set.insert(person("Hugo", "Boss"));
	person_set.insert(person("Armin", "Assinger"));
	copy(person_set.begin(), person_set.end(),
			ostream_iterator<person>(cout, "\n"));
	person_set.insert(student("Franz", "Mayr", "se000164"));
	copy(person_set.begin(), person_set.end(),
			ostream_iterator<person>(cout, "\n"));
}

static void simple_pointer_test() {
	set<person*> person_set;
	person_set.insert(new person("Hugo", "Boss"));
	person_set.insert(new person("Armin", "Assinger"));
	for (auto person : person_set) {
		cout << (*person) << endl;
	}
	person_set.insert(new student("Franz", "Mayr", "se000164"));
	for (auto person : person_set) {
		cout << (*person) << endl;
	}
	for_each(person_set.begin(), person_set.end(), ([](const person* p) {
		delete p;
	}));
}

bool operator<(const scoped_ptr<person>&scopedP1,
		const scoped_ptr<person> &scopedP2) {
	return *scopedP1 < *scopedP2;
}

static void scoped_pointer_test() {
	scoped_ptr<person> sc1(new person("Hugo", "Boss"));
	cout << *sc1 << endl;

	scoped_ptr<person> sc2(sc1);
	cout << *sc2 << endl;
	// will fail because ownership has been moved
//	cout << *sc1 << endl;

	set<scoped_ptr<person>> person_set;
	// The set wants to copy the scoped pointer held pointer which causes a segmentation fault because scoped pointer has not ownership anymore.
//	person_set.insert(scoped_ptr<person>(new student("Franz", "Maier", "se00001")));
}

bool operator<(const unique_ptr<person> &np1, const unique_ptr<person> &np2) {
	return *np1 < *np2;
}

/**
 * Unique_ptr shall be used if only one owner is meant to be guaranteed.
 */
static void unique_pointer_test() {
	unique_ptr<person> up1(new person("unique", "pointer"));
	cout << *up1 << endl;

	unique_ptr<person> up2 = move(up1);
	cout << up1.get() << endl;
	cout << *up2 << endl;

	set<unique_ptr<person>> person_set;
	person_set.insert(unique_ptr<person>(new person("hugo", "boss")));
	person_set.insert(unique_ptr<person>(new person("franz", "meister")));
	person_set.insert(
			unique_ptr<person>(new student("hugo", "boss", "s00002")));

	for (auto person = begin(person_set); person != end(person_set); person++) {
		cout << **person << endl;
	}
}

bool operator<(const counted_pointer<person>& p1,
		const counted_pointer<person>& p2) {
	return *p1 < *p2;
}

/**
 * With this counted_pointer type an grabage collection is implicit possible.
 * If the last reference is deleted the object will get deleted.
 * This only works if all of the objects are wrapped in counted_pointer instances.
 */
static void counted_pointer_test() {
	counted_pointer<person> cp1(new person("thoms", "herog"));
	counted_pointer<person> cp2(cp1);

	cout << *cp1 << endl;
	cout << *cp2 << endl;

	set<counted_pointer<person>> person_set;
	person_set.insert(counted_pointer<person>(new person("thomas", "herzog")));
	person_set.insert(counted_pointer<person>(new person("hugo", "maier")));
	person_set.insert(
			counted_pointer<person>(
					new student("thomas", "herzog", "s000001")));

	for (auto person : person_set) {
		cout << *person << endl;
	}

	set<counted_pointer<person>> person_set2(person_set);
	for (auto person : person_set) {
		cout << *person << endl;
	}
	for (auto person : person_set2) {
		cout << *person << endl;
	}

}

static void shared_pointer_test() {
	// Exceptions are not able to be handled if an exception is thrown in the constructor.
//	shared_ptr<person> p(new person("thoms", "herzog"));
	shared_ptr<person> sp1 = make_shared<person>(person("thoms", "herzog"));
	shared_ptr<person> sp2(sp1);
	cout << *sp1 << endl;
	cout << *sp2 << endl;

	// set would sort by the pointer address
	// shared_ptr has already overwritten the operator<
	// therefore we need an comparator set on the set instance
//	set<shared_ptr<person>> person_set;
	set<shared_ptr<person>,
			bool (*)(const shared_ptr<person>, const shared_ptr<person>)> person_set(
			([](shared_ptr<person> p1, shared_ptr<person> p2) {
				return *p1 < *p2;
			}));

	person_set.insert(make_shared<person>(person("hugo", "boss")));
	person_set.insert(make_shared<person>(person("maria", "maier")));
	person_set.insert(make_shared<student>(student("hugo", "boss", "s000001")));

	for (auto person : person_set) {
		cout << *person << endl;
	}
}

int main() {
	cout << "============================\n" << "===== collection tests =====\n"
			<< "============================\n" << endl;

	cout << "----- static objects -----" << endl;
	static_collection_test();
	cout << "==========================\n" << endl;

	cout << "----- simple pointers -----" << endl;
	simple_pointer_test();
	cout << "===========================\n" << endl;

	cout << "----- scoped pointers -----" << endl;
	scoped_pointer_test();
	cout << "===========================\n" << endl;

	cout << "----- unique pointers (STL) -----" << endl;
	unique_pointer_test();
	cout << "=================================\n" << endl;

	cout << "----- counted pointers -----" << endl;
	counted_pointer_test();
	cout << "============================\n" << endl;

	cout << "----- shared pointers (STL) -----" << endl;
	shared_pointer_test();
	cout << "=================================\n" << endl;

}
