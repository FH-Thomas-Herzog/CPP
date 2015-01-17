/*
 * List.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: cchet
 */
#include "List.h"
#include "Node.h"
#include <string>
#include <cassert>

using namespace ML;
using namespace std;

List::List() :
		start(nullptr), size(0) {
	Register("List", "Collection");
}

List::~List() {
	Clear();
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
	assert(CheckList());
	Node* foundNode = Find(object);
	if (foundNode == nullptr) {
		return nullptr;
	} else if (foundNode->prev == nullptr) {
		start = foundNode->next;
		if (start->next != nullptr) {
			start->next->prev = start;
		}
	} else {
		foundNode->prev->next = foundNode->next;
		if (foundNode->next != nullptr) {
			foundNode->next->prev = foundNode->prev;
		}
	}
	Object* value = foundNode->val;
	delete foundNode;
	size--;
	assert(CheckList());
	return value;
}

void List::Clear() {
	Node* next;
	while (start != nullptr) {
		next = start->next;
		delete start;
		start = next;
	}
	start = nullptr;
	size = 0;
	assert(CheckList());
}

Iterator* List::NewIterator() const {
	return nullptr;
}

bool List::CheckList() const {
	if (start == nullptr) {
		return size == 0;
	} else {
		Node* prev = nullptr;
		Node* node = start;
		int tmpSize = 1;
		while (node->next != nullptr) {
			if (node->prev != prev) {
				return false;
			}
			prev = node;
			node = node->next;
			tmpSize++;
		}
		return size == tmpSize;
	}
}

Node* List::Find(Object* object) const {
	Node* cur = start;
	while ((cur != nullptr) && (cur->val->IsEqualTo(object))) {
		cur = cur->next;
	}
	return cur;
}

void List::Prepend(Object* object) {
	assert(CheckList());
	Node* node = new Node(object, nullptr, start);
	if (start != nullptr) {
		start->prev = node;
	}
	start = node;
}

void List::Append(Object* object) {
	assert(CheckList());
	if (start == nullptr) {
		start = new Node(object);
	} else {
		Node* cur = start;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		cur->next = new Node(object, cur, nullptr);
		assert(CheckList());
	}
	size++;
}

ListIterator::ListIterator(Node* head) :
		current(head) {
	Register("ListIterator", "Iterator");
}

ListIterator::~ListIterator() {
	// do nothing. current Node lifecylce managed by list not iterator
}

Object* ListIterator::Next() {
	if (current == nullptr) {
		return nullptr;
	} else {
		Object* object = current->val;
		current = current->next;
		return object;
	}
}

