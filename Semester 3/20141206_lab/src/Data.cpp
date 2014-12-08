/*
 * Data.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: cchet
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "Data.h"

using namespace std;

Data::Data(string val) :
		value(val) {
	cout << "constructor of Data('" << value << "') called" << endl;
}

Data::~Data() {
	cout << "destructor of Data('" << value << "') called" << endl;
}

Data::operator std::string() const {
	cout << "Cast operator to string for Data " << value << "called" << endl;
	return value;
}

bool Data::operator==(const Data& d) const {
	return value == d.value;
}

ostream& operator<<(ostream& os, Data& d) {
	d.print(os);
	return os;
}

void Data::print(ostream& os) const{
	os << "\\" << value << "\\" << flush;
}
