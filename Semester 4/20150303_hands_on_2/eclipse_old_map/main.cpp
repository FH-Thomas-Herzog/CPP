/*
 * main.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: cchet
 */
#include "HashTable.hpp"

using namespace std;

int main(int argc, char** argv) {
	HashTable<string, std::hash<string>, std::equal_to<string>> table;
	string sw1("HEllo");
	string sw2("HEllo");
	table.insert(sw1);
	table.insert(sw2);
	return 0;
}

