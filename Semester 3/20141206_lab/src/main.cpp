/*
 * main.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: cchet
 */
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include "PQueue.h"
#include "PData.h"

using namespace std;

int main() {
	/*Queue q1;*/
	PQueue q2(10);
	cout << "02:" << q2 << endl;
	q2.enqueue(new PData("hello", 3));
	q2.enqueue(new PData("world", 2));
	q2.enqueue(new PData("over there", 1));
	cout << "02:" << q2 << endl;
	q2.clear();
	PQueue q3 = q2;

	q3.enqueue(new PData("new value", 1));

	for (int i = 0; i < 8; i++) {
		stringstream ss;
		ss << "Wert" << i;
		q2.enqueue(new PData(ss.str(), i));
		q3.enqueue(new PData(ss.str(), i));
	}
	cout << q3;
	while (!q3.isEmpty()) {
		cout << *q3.dequeue() << endl; // memory leak;
		Data *d = q3.dequeue();
		cout << *d << endl;
		delete d;
	}

	Queue *q5 = new PQueue(10);
	q5->enqueue(new PData("dynamic", 1));
	q5->enqueue(new PData("queues", 2));
	q5->enqueue(new PData("are", 3));
	q5->enqueue(new PData("best", 4));

	q5->clear();

	delete q5;

	return 0;
}

