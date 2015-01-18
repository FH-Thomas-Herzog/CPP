/*
 * Bag.cpp
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */
#include "Bag.h"

using namespace std;
using namespace ML;

Bag::Bag() :
		Set() {
	Register("Bag", "Set");
} /* Bag::Bag */

Bag::~Bag() {
	// Nothing to do
} /* Bag::~Bag */

BagNode* Bag::Find(Object* object) const {
	/* Save for brutal cast because only BagNode instances are allowed */
	return (BagNode*) Set::Find(object);
}/* Bag::Find */

void Bag::Add(Object* object) {
	Append(object);
} /* Bag::Add */

void Bag::Append(Object* object) {
	BagNode* node = Find(object);
	/* no duplicates, so parent can handle */
	if (node == nullptr) {
		BagNode* newNode = new BagNode(object, anchor->next->prev,
				anchor->next);
		anchor->next = newNode;
		newNode->next->prev = newNode;
	}
	/* increase count */
	else {
		node->count++;
	} /* if */
	size++;
} /* Bag::Append */

void Bag::Prepend(Object* object) {
	BagNode* node = Find(object);
	/* no duplicates, so parent can handle */
	if (node == nullptr) {
		BagNode* newNode = new BagNode(object, anchor->prev,
				anchor->prev->next);
		anchor->prev = newNode;
		newNode->prev->next = newNode;
	}
	/* increase count */
	else {
		node->count++;
	} /* if */
	size++;
} /* Bag::Prepend */

Object* Bag::Remove(Object* object) {
	BagNode* node = Find(object);
	/* if node found and has duplicates */
	if ((node != nullptr) && (node->count > 1)) {
		node->count--;
		size--;
		return object;
	}
	/* else delegate to parent class */
	else {
		return Set::Remove(object);
	} /* if */
} /* Bag::Remove */

void Bag::Intersect(Bag* bag) {
	Set::Intersect(bag);
} /* Bag::Intersect */

void Bag::Union(Bag* bag) {
	if (bag == nullptr) {
		cout << "Given Bag is not allowed to be null !!!" << endl << flush;
	} else if (bag->Size() > 0) {
		Iterator* it = bag->NewIterator();
		Object* obj = it->Next();
		BagNode* node = nullptr;
		while (obj != nullptr) {
			/* node found in this bag */
			if ((node = Find(it->Next())) == nullptr) {
				Append(obj);
				for (int i = 1; i < node->count; ++i) {
					Append(obj);
				} /* for */
			} /* if */
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Bag::Union */

void Bag::Complement(Bag* bag) {
	Set::Complement(bag);
} /* Bag::Complement */

ostream& operator<<(ostream & os, const Bag & bag) {
	bag.Print(os, bag);
	return os;
} /* operator<< */
