/*
 * main.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: cchet
 */
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "T9.h"

using namespace std;

int main(int argc, char** argv) {
	T9Converter handler;
	try {
		cout << "a=" << handler.char2Digit('a') << endl;
		cout << "z=" << handler.char2Digit('z') << endl;
		cout << "z=" << handler.word2Number("kiss") << endl;
	} catch (InvalidConversionException e) {
		cout << "error";
		cout << endl << "Error thrown:" << endl << e.what();
	}
	return EXIT_SUCCESS;
}

