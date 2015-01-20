/*
 * List.cpp
 * This is the implementation of the List container specification.
 *
 *  Created on: Jan 17, 2015
 *      Author: Thomas Herzog
 */
#include "List.h"
#include <string>
#include <cassert>

using namespace ML;
using namespace std;

List::List() :
		size(0) {
	Register("List", "Collection");
	/* init anchor peropely */
	Node* node = new Node();
	node->next = node;
	node->prev = node;
	anchor = node;
} /* List::List */

List::~List() {
	Clear();
	delete anchor;
} /* List::~List */

int List::Size() const {
	return size;
} /* List::Size */

void List::Add(Object* object) {
	Append(object);
} /* List::Add */

bool List::Contains(Object* object) const {
	return Find(object) != nullptr;
} /* List::Contains */

Object* List::Remove(Object* object) {
	Object* value = nullptr;
	Node* foundNode = Find(object);
	if (foundNode != nullptr) {
		foundNode->prev->next = foundNode->next;
		foundNode->next->prev = foundNode->prev;
		value = foundNode->val;
		delete foundNode;
		size--;
	} /* if */
	return value;
} /* List::Remove */

void List::Clear() {
	Node* next = nullptr;
	Node* node = anchor->next;
	while (node != anchor) {
		next = node->next;
		delete node;
		node = next;
	} /* if */
	anchor->next = anchor;
	anchor->prev = anchor;
	size = 0;
} /* List::Clear */

Iterator* List::NewIterator() const {
	return new ListIterator(anchor, anchor->next);
} /* List::NewIterator */

Node* List::Find(Object* object) const {
	Node* node = anchor->next;
	while ((node != anchor) && (!node->val->IsEqualTo(object))) {
		node = node->next;
	} /* while */
	return ((node != anchor) ? node : nullptr);
} /* List::Find */

void List::Prepend(Object* object) {
	Node* newNode = new Node(object, anchor->prev,
			anchor->prev->next);
	anchor->prev = newNode;
	newNode->prev->next = newNode;
	size++;
} /* List::Prepend */

void List::Append(Object* object) {
	Node* newNode = new Node(object, anchor->next->prev,
			anchor->next);
	anchor->next = newNode;
	newNode->next->prev = newNode;
	size++;
} /* List::Append */

void List::Print(ostream & os) const {
	os << "-----------------" << endl <<  Class() << "(" << size << "):" << endl
			<< "-----------------" << endl;
	Node* node = anchor->next;
	while (node != anchor) {
		os << node->AsString();
		node = node->next;
		if (node != anchor) {
			os << ", ";
		} /* if */
	} /* while */
} /* List::Print */

ostream& operator<<(ostream & os, const List & list) {
	list.Print(os);
	return os;
} /* operator<< */

// #########################################################
// Iterator implementation
// #########################################################
ListIterator::ListIterator(Node* anchorNode, Node* start) :
		anchorNode(anchorNode), current(start) {
	Register("ListIterator", "Iterator");
} /* ListIterator::ListIterator */

ListIterator::~ListIterator() {
	// do nothing. current Node lifecylce managed by list not iterator
} /* ListIterator::~ListIterator */

Object* ListIterator::Next() {
	Object* object = nullptr;
	if (current != anchorNode) {
		object = current->val;
		current = current->next;
	} /* if */
	return object;
} /* ListIterator::Next */

