/*
 * main.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: cchet
 */
#include <string>
#include <iostream>
#include <cassert>
#include "Queue.h"

using namespace std;

int main() {

	/*Queue q1;*/
	Queue q2(10);

	cout << "02:" << q2 << endl;
	q2.enqueue(new Data("hello"));
	q2.enqueue(new Data("world"));
	q2.enqueue(new Data("over there"));
	cout << "02:" << q2 << endl;
	q2.clear();
	Queue q3 = q2;

	q3.enqueue(new Data("new value"));

	while (!q3.isEmpty()) {
		cout << *q3.dequeue() << endl; // memory leak;
		Data *d = q3.dequeue();
		cout << *d << endl;
		delete d;
	}

	Queue *q5 = new Queue(10);
	q5->enqueue(new Data("dynamic"));
	q5->enqueue(new Data("queues"));
	q5->enqueue(new Data("are"));
	q5->enqueue(new Data("best"));

	q5->clear();

	delete q5;

	return 0;
}

