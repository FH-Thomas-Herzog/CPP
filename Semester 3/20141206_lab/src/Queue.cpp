//============================================================================
// Name        : Queue.cpp
// Author      : Thomas Herzog
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cassert>
#include "Queue.h"

using namespace std;

Queue::Queue(int cp) :
		start(0), count(0), capacity(cp) {
	cout << "Constructor Queue (" << cp << ") called!" << endl;
	data = new Data*[capacity];
}

Queue::~Queue() {
	cout << "Destructor Queue() called!" << endl;
	clear();
}

Queue::Queue(const Queue& q) :
		start(q.start), count(q.count), capacity(q.capacity) {
	data = new Data*[capacity];
	for (int i = 0; i < count; ++i) {
		data[at(i)] = q.data[at(i)];
	}
}

bool Queue::isEmpty() const {
	return count == 0;
}

bool Queue::isFull() const {
	return count == capacity;
}

void Queue::enqueue(Data* item) {
	assert(!isFull());
	data[at(count)] = item;
	count++;
}

Queue& Queue::operator=(const Queue& q) {
	if (&q == this)
		return *this;
	if (capacity != q.capacity) {
		delete[] data;
		capacity = q.capacity;
		data = new Data*[capacity];
	}
	start = q.start;
	count = q.count;
	for (int i = 0; i < count; ++i) {
		data[at(i)] = q.data[at(i)];
	}
	return *this;
}

bool Queue::operator==(const Queue& q) {
	if (&q == this) {
		return false;
	} else if (q.capacity != capacity) {
		return false;
	} else if (q.count != count) {
		return false;
	} else {
		for (int i = 0; i < count; ++i) {
			Data* d1 = data[at(i)];
			Data* d2 = q.data[at(i)];
			if (*d1 != *d2) {
				return false;
			}
		}
	}
	return true;
}

Data* Queue::dequeue() {
	assert(!isEmpty());
	Data* item = data[start];
	start = at(1);
	return item;
}

void Queue::clear() {
	while (!isEmpty()) {
		Data* item = dequeue();
		delete item;
	}
}

void Queue::print(ostream &os) const {
	os << "{";
	for (int i = 0; i < count; ++i) {
		if (i > 0) {
			os << ", ";
		}
		os << *data[at(i)];
	}
	os << "}" << flush;
}

ostream& operator<<(ostream& os, const Queue& queue) {
	queue.print(os);
	return os;
}
