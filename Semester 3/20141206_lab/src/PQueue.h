/*
 * PQueue.h
 *
 *  Created on: Dec 6, 2014
 *      Author: cchet
 */

#ifndef PQUEUE_H_
#define PQUEUE_H_

#include <iostream>
#include "Queue.h"

class PQueue: public Queue {

protected:
	int getPriority(Data* item) const;
	int getPriority(int i) const;
	void swap(int i, int level);
	bool isHeap() const;

public:
	PQueue(int capacity);
	virtual ~PQueue();

	virtual bool isEmpty() const;
	virtual bool isFull() const;
	virtual void enqueue(Data* item);
	virtual Data* dequeue();
	virtual void print(std::ostream &os) const;
	void print(std::ostream &os, int i, int level) const;
};

#endif /* PQUEUE_H_ */
