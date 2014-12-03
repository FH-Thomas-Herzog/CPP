/*
 * main.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: cchet
 */
#include <iostream>
#include "rational.h"

using namespace swo3;
using namespace std;

int main() {
	Rational r1(1, 4);
	Rational r2(1, 8);

	cout << r1 << endl;
	cout << r2 << endl;

	Rational r3 = r1 + r2;

	cout << r3 << endl;
}

