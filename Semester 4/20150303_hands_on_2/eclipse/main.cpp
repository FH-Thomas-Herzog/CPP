/*
 * main.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: cchet
 */
#include "hashtable_template.hpp"

using namespace std;

int main(int argc, char** argv) {
	hashtable<string, std::hash<string>, std::equal_to<string>> theTable(3);
	theTable.insert(string("a"));
	theTable.insert(string("b"));
	theTable.insert(string("c"));
	theTable.insert(string("d"));
	theTable.insert(string("e"));

	int i = 0;
	for (auto it = theTable.begin(); it != theTable.end(); it++) {
		cout << i << ". " << (*it) << endl;
		i++;
	}

	cout << theTable << flush << endl;
	return 0;
}

