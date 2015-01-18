/*
 * Set.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */
#include "Set.h"

using namespace std;
using namespace ML;

Set::Set() :
		List() {
	Register("Set", "List");
	// Nothing to do. List initializes backed container
}

Set::~Set() {
	// Nothing to do
}

bool Set::IsAlreadyManaged(Object* object) const {
	Node* node = Find(object);
	if (node != nullptr) {
		cout << "Object already managed by this set !!!" << endl << flush;
	}
	return node != nullptr;
}

void Set::Add(ML::Object* object) {
	if (!IsAlreadyManaged(object)) {
		List::Add(object);
	}
}

void Set::Append(ML::Object* object) {
	if (!IsAlreadyManaged(object)) {
		List::Append(object);
	}
}

void Set::Prepend(ML::Object* object) {
	if (!IsAlreadyManaged(object)) {
		List::Prepend(object);
	}
}

void Set::Intersect(Set* set) {
	if (set == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	} else if (set->Size() == 0) {
		Clear();
	} else {
		Iterator* it = NewIterator();
		Object* obj = it->Next();
		while (obj != nullptr) {
			if (set->Find(obj) == nullptr) {
				Remove(obj);
			}
			obj = it->Next();
		}

		delete it;
	}
}

void Set::Union(Set* set) {
	if (set == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	} else if (set->Size() > 0) {
		Iterator* it = set->NewIterator();
		Object* obj = it->Next();
		while (obj != nullptr) {
			if (Find(obj) == nullptr) {
				Append(obj);
			}
			obj = it->Next();
		}

		delete it;
	}
}

void Set::Complement(Set* set) {
	if (set == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	} else if (set->Size() > 0) {
		Iterator* it = set->NewIterator();
		Object* obj = it->Next();
		while (obj != nullptr) {
			if (Find(obj) != nullptr) {
				Remove(obj);
			}
			obj = it->Next();
		}

		delete it;
	}
}
