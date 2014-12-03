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

	return 0;
}

