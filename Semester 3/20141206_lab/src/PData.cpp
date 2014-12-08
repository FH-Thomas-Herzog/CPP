/*
 * PData.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: cchet
 */
#include <string>
#include <iostream>
#include "PData.h"

using namespace std;

PData::PData(string value, int priority) :
		Data(value), priority(priority) {
	cout << "Constructor PData (" << value << ") PRIO (" << priority
			<< ") called" << flush << endl;
}

PData::~PData() {
	cout << "Destructor PData (" << value << ") PRIO (" << priority
			<< ") called" << flush << endl;
}

int PData::getPriority() const {
	return priority;
}

void PData::print(ostream &os) const {
	/* Calls superclass implementation */
	Data::print(os);
	os << "(" << priority << ")" << flush;
}
