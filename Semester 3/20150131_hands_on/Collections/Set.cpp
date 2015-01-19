/*
 * Set.cpp
 * This is the implementation of the Set container specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */
#include "Set.h"

using namespace std;
using namespace ML;

Set::Set() :
		List() {
	Register("Set", "List");
	// Nothing to do. List initializes backed container
} /* Set::Set */

Set::~Set() {
	// Nothing to do
} /* Set::~Set */

bool Set::IsAlreadyManaged(Object* object) const {
	Node* node = Find(object);
	if (node != nullptr) {
		cout << "Object already managed by this set !!!" << endl << flush;
	} /* if */
	return node != nullptr;
} /* Set::IsAlreadyManaged */

void Set::Add(ML::Object* object) {
	/* avoid duplicates */
	if (!IsAlreadyManaged(object)) {
		List::Add(object);
	} /* if */
} /* Set::Add */

void Set::Append(ML::Object* object) {
	/* avoid duplicates */
	if (!IsAlreadyManaged(object)) {
		List::Append(object);
	} /* if */
} /* Set::Append */

void Set::Prepend(ML::Object* object) {
	/* avoid duplicates */
	if (!IsAlreadyManaged(object)) {
		List::Prepend(object);
	} /* if */
} /* Set::Prepend */

void Set::Intersect(Set* set) {
	/* null set not allowed will not change anything */
	if (set == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	}
	/* if source is empty this set cannot contain any element */
	else if (set->Size() == 0) {
		Clear();
	}
	/* find out what to nodes are supposed to be removed */
	else {
		Iterator* it = NewIterator();
		Object* obj = it->Next();
		while (obj != nullptr) {
			if (set->Find(obj) == nullptr) {
				Remove(obj);
			} /* if */
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Set::Intersect */

void Set::Union(Set* set) {
	/* null set not allowed will not change anything */
	if (set == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	}
	/* if source wmpty nothign to do */
	else if (set->Size() > 0) {
		Iterator* it = set->NewIterator();
		Object* obj = it->Next();
		while (obj != nullptr) {
			if (Find(obj) == nullptr) {
				Append(obj);
			} /* if */
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Set::Union */

void Set::Complement(Set* set) {
	/* null set not allowed will not change anything */
	if (set == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	}
	/* if source is empt nothing to do */
	else if (set->Size() > 0) {
		Iterator* it = set->NewIterator();
		Object* obj = it->Next();
		while (obj != nullptr) {
			if (Find(obj) != nullptr) {
				Remove(obj);
			} /* if */
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Set::Complement */
