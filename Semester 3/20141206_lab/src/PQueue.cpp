//============================================================================
// Name        : PQueue.cpp
// Author      : Thomas Herzog
// Version     :
// Copyright   : open for anybody
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <assert.h>
#include "PQueue.h"
#include "PData.h"

using namespace std;

//////////////////////////////////////////
// Global helpers
/////////////////////////////////////////
static int parent(int i) {
	return i / 2;
}

static int left(int i) {
	return i * 2;
}

static int right(int i) {
	return (i * 2) + 1;
}

//////////////////////////////////////////
// De-, Constructors
/////////////////////////////////////////
PQueue::PQueue(int capacity) :
		Queue(capacity + 1) {
	start = 1;
	cout << "Constructor PQueue(" << capacity << ") called" << flush << endl;
}

PQueue::~PQueue() {
	cout << "Destructor PQueue(" << capacity << ") called" << flush << endl;
}

//////////////////////////////////////////
// overwritten functions
/////////////////////////////////////////
int PQueue::getPriority(Data *item) const {
	PData *pItem = dynamic_cast<PData*>(item);
	if (pItem != nullptr) {
		return pItem->getPriority();
	}
	return 0;
}

int PQueue::getPriority(int i) const {
	return getPriority(data[i]);
}

void PQueue::swap(int i, int j) {
	Data* temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

bool PQueue::isEmpty() const {
	return count == 0;
}

bool PQueue::isFull() const {
	return count == (capacity - 1);
}

bool PQueue::isHeap() const {
	for (int i = 2; i < count; i++) {
		if (getPriority(i) > (getPriority(parent(i)))) {
			return false;
		}
	}
	return true;
}

void PQueue::enqueue(Data* item) {
	assert(!isFull());
	count++;
	data[count] = item;
	int i = count;
	while ((i > 1) && (getPriority(i) > getPriority(parent(i)))) {
		swap(i, parent(i));
		i = parent(i);
	}
	assert(isHeap());
}

void PQueue::print(ostream &os) const {
	os << "(" << endl;
	print(os, 1, 1);
}

void PQueue::print(ostream &os, int i, int level) const {
	if (i > count) {
		return;
	}
	os << string(level * 2, ' ') << *data[i] << endl;
	print(os, left(i), level + 1);
	print(os, right(i), level + 1);
}

Data* PQueue::dequeue() {
	assert(!isFull());
	Data* item = data[1];
	count--;
	int i = 1;

	while (left(i) <= count) {
		int j = ((right(i) >= count)
				|| (getPriority(left(i)) > getPriority(right(i)))) ?
				right(i) : left(i);
		if (getPriority(i) < getPriority(j)) {
			break;
		}
		i = j;
	}

	assert(isHeap());
	return item;
}
