/*
 * person_main.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: cchet
 */
#include "person.h"

using namespace swo3;

int main() {
	Person p;
	p.setName("Thomas Herzog");
	p.print();
	p.~Person();
}

