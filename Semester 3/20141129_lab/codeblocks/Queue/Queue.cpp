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
		start(0), stop(0), count(0), capacity(cp) {
	cout << "Constructor Queue (int cp) " << cp << "called!" << endl;
	data = new Data*(capacity);
}

Queue::~Queue() {
	delete[] data;
}

bool isEmpty const {
	return count == 0;
}

bool isFull const {
	return count == capacity;
}

void Queue::enqueue(Data* item) {
	assert(!isFull);
	data[at(count)] = item;
	count++;
}

Data* Queue::dequeue() {
	assert(!isEmpty());
	Data* item = data[start];
	start = at(1);
}

ostream& operator<<(ostream& os, const Queue& queue) {
	os << "{";
	for (int i = 0; i < queue.count; ++i) {
		if (i > 0) {
			os << ", ";
		}
		os << *queue.data[queue.at[i]];
	}
	os << "}";
}
