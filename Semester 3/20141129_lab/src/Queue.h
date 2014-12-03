/*
 * Queue.h
 *
 *  Created on: Nov 29, 2014
 *      Author: cchet
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <string>
#include "Data.h"

class Queue {

protected:
	int start;
	int capacity;
	int count;
	Data** data;
	inline int at(int i) const {
		return (start + i) % capacity;
	}

public:
	explicit Queue(int cp);
	Queue(const Queue& queue);
	virtual ~Queue(void);

	virtual bool isEmpty(void) const;
	virtual bool isFull(void) const;

	virtual void enqueue(Data* item);
	virtual Data* dequeue(void);
	virtual void clear(void);
	virtual Queue& operator=(const Queue& q);
	virtual bool operator==(const Queue& q);
	inline bool operator!=(const Queue& q) {
		return !operator ==(q);
	}

	friend std::ostream& operator<<(std::ostream & os, const Queue & s);
};
#endif /* QUEUE_H_ */
