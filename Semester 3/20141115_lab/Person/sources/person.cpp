/*
 * person.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: cchet
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "person.h"

using namespace std;

namespace swo3 {

Person::Person() {
	name = 0;
	cout << "Default constructor called" << endl;
}

Person::~Person() {
	free(name);
	name = 0;
	cout << "Default destructor called" << endl;
}

Person::Person(const char* name) :
		name(strdup(name)) {
}

void Person::setName(const char* name) {
	if (this->name != 0) {
		free(this->name);
	}
	this->name = strdup(name);
	cout << "Name set on person = " << name << endl;
}

void Person::print() const {
	cout << "Person: " << name << endl;
}

}
