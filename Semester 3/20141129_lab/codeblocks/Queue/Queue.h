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

class Queue {

private:
	int start;
	int stop;
	int capacity;
	int count;
	Data **data;
	inline int at(int i) const {
		return (start + i) % capacity;
	}

public:
	Queue(int cp);
	~Queue();

	bool isEmpty() const;
	bool isFull() const;

	void enqueue(Data* item);
	Data* dequeue();

	friend std::ostream& operator<<(std::ostream, const Queue& queue);
};
#endif /* QUEUE_H_ */
