/*
 * IndexV4.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: cchet
 */
#include "utils.hpp"
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


typedef map<string, set<int>> wordMap;
static int curLineNr = 0;
static wordMap entryMap;

static void addWord(string word) {
	set<int>& lineNumbers = entryMap[normalize(word)];
	lineNumbers.insert(curLineNr);
}

void IndexV4(int argc, char** argv) {
	ifstream fis;
	string line;
	openStream(argc, argv, fis);

	while (fis.good()) {
		curLineNr++;
		getline(fis, line);
		stringstream ss(line);
		for_each(istream_iterator<string>(ss), istream_iterator<string>(),
				addWord);
	}

	fis.close();

	for(wordMap::iterator it = entryMap.begin(); it != entryMap.end(); it++) {
		cout << setw(15) << it->first << ": ";
		copy(it->second.begin(), it->second.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
	}

	cout << endl << "Elements: " << entryMap.size() << endl;
}


