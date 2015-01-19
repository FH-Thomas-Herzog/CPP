/*
 * Bag.cpp
 * This is the implementation of the bag container specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
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
	/* no duplicates, normal append */
	if (node == nullptr) {
		BagNode* newNode = new BagNode(object, anchor->prev,
				anchor->prev->next);
		anchor->prev = newNode;
		newNode->prev->next = newNode;
	}
	/* else increase count of duplicates */
	else {
		node->count++;
	} /* if */
	size++;
} /* Bag::Append */

void Bag::Prepend(Object* object) {
	BagNode* node = Find(object);
	/* no duplicates, normal prepend */
	if (node == nullptr) {
		BagNode* newNode = new BagNode(object, anchor->next->prev,
				anchor->next);
		anchor->next = newNode;
		newNode->next->prev = newNode;
	}
	/* else increase count of duplicates */
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
	if (bag == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	} else if (bag->Size() == 0) {
		Clear();
	} else {
		Iterator* it = NewIterator();
		Object* obj = it->Next();
		BagNode* bagNode = nullptr;
		BagNode* thisNode = nullptr;
		while (obj != nullptr) {
			thisNode = Find(obj);
			/* node not present in source bag */
			if ((bagNode = bag->Find(obj)) == nullptr) {
				/* remove all nodes with duplicates */
				size -= (thisNode->count - 1);
				Remove(obj);
			}
			/* append as much as common */
			else if (thisNode->count > bagNode->count) {
				/* remove too much duplicates */
				int diff = (thisNode->count - bagNode->count);
				thisNode->count = (thisNode->count - diff);
				size -= diff;
			}/* if */
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Bag::Intersect */

void Bag::Union(Bag* bag) {
	if (bag == nullptr) {
		cout << "Given Bag is not allowed to be null !!!" << endl << flush;
	} else if (bag->Size() > 0) {
		Iterator* it = bag->NewIterator();
		Object* obj = it->Next();
		BagNode* bagNode = nullptr;
		BagNode* thisNode = nullptr;
		while (obj != nullptr) {
			bagNode = bag->Find(obj);
			/* node found in this bag */
			if ((thisNode = Find(obj)) == nullptr) {
				Append(obj);
				Find(obj)->count += (bagNode->count - 1);
				size += (bagNode->count - 1);
				/* for */
			}
			else if (thisNode->count < bagNode->count) {
				int diff = (bagNode->count - thisNode->count);
				size+=diff;
				thisNode->count+=diff;
			}
			/* if */
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Bag::Union */

void Bag::Complement(Bag* bag) {
	if (bag == nullptr) {
		cout << "Given set is not allowed to be null !!!" << endl << flush;
	} else if (bag->Size() > 0) {
		Iterator* it = bag->NewIterator();
		Object* obj = it->Next();
		BagNode* thisNode = nullptr;
		BagNode* bagNode = nullptr;
		while (obj != nullptr) {
			if ((thisNode = Find(obj)) != nullptr) {
				bagNode = bag->Find(obj);
				/* Only remove to much duplicates */
				if (thisNode->count > bagNode->count) {
					thisNode-=bagNode->count;
					size-=bagNode->count;
				}
				/* if source has more then this bag remove all */
				else if (bagNode->count >= thisNode->count) {
					size-=(thisNode->count - 1);
					thisNode->count = 1;
					Remove(obj);
				}/* if */
			}
			obj = it->Next();
		} /* while */

		delete it;
	} /* if */
} /* Bag::Complement */

ostream& operator<<(ostream & os, const Bag & bag) {
	bag.Print(os);
	return os;
} /* operator<< */
