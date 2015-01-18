/*
 * List.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: cchet
 */
#include "List.h"
#include <string>
#include <cassert>

using namespace ML;
using namespace std;

List::List() :
		size(0) {
	Register("List", "Collection");
	Node* node = createWrapperInstance(nullptr, nullptr, nullptr);
	node->next = node;
	node->prev = node;
	anchor = node;
}

List::~List() {
	Clear();
	delete anchor;
}

int List::Size() const {
	return size;
}

void List::Add(Object* object) {
	Append(object);
}

bool List::Contains(Object* object) const {
	return Find(object) != nullptr;
}

Object* List::Remove(Object* object) {
	Object* value = nullptr;
	Node* foundNode = Find(object);
	if (foundNode != nullptr) {
		foundNode->prev->next = foundNode->next;
		foundNode->next->prev = foundNode->prev;
		value = foundNode->val;
		delete foundNode;
		size--;
	}
	return value;
}

void List::Clear() {
	Node* next = nullptr;
	Node* node = anchor->next;
	while (node != anchor) {
		next = node->next;
		delete node;
		node = next;
	}
	anchor->next = anchor;
	anchor->prev = anchor;
	size = 0;
}

Iterator* List::NewIterator() const {
	return new ListIterator(anchor, anchor->next);
}

Node* List::Find(Object* object) const {
	Node* node = anchor->next;
	while ((node != anchor) && (!node->val->IsEqualTo(object))) {
		node = node->next;
	}
	return ((node != anchor) ? node : nullptr);
}

void List::Prepend(Object* object) {
	Node* newNode = createWrapperInstance(object, anchor->next->prev,
			anchor->next);
	anchor->next = newNode;
	newNode->next->prev = newNode;
	size++;
}

void List::Append(Object* object) {
	Node* newNode = createWrapperInstance(object, anchor->prev,
			anchor->prev->next);
	anchor->prev = newNode;
	newNode->prev->next = newNode;
	size++;
}

Node* List::createWrapperInstance(ML::Object* object, Node* prev,
		Node* next) const {
	return new Node(object, prev, next);
}

ostream& operator<<(ostream & os, const List & list) {
	os << "-----------------" << endl <<  "List(" << list.Size() << "):" << endl
			<< "-----------------" << endl;
	Node* node = list.anchor->next;
	while (node != list.anchor) {
		os << node->AsString();
		if (node != list.anchor) {
			os << ", ";
		}
		node = node->next;
	}
	return os;
} /* operator<< */

// #########################################################
// Iterator implementation
// #########################################################
ListIterator::ListIterator(Node* anchorNode, Node* start) :
		anchorNode(anchorNode), current(start) {
	Register("ListIterator", "Iterator");
}

ListIterator::~ListIterator() {
	// do nothing. current Node lifecylce managed by list not iterator
}

Object* ListIterator::Next() {
	Object* object = nullptr;
	if (current != anchorNode) {
		object = current->val;
		current = current->next;
	}
	return object;
}

