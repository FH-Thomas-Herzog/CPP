/*
 * IndexV3.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: cchet
 */
#include "utils.hpp"
#include "Entry.h"
#include <fstream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

static set<Entry> entrySet;
static int curLineNr = 0;

static void addWord(string word) {
	Entry e(normalize(word));
	pair<set<Entry>::const_iterator, bool> entryPair = entrySet.insert(e);

	const_cast<Entry&>(*(entryPair.first)).addLineNr(curLineNr);
}

void IndexV3(int argc, char** argv) {
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

	copy(entrySet.begin(), entrySet.end(), ostream_iterator<Entry>(cout, "\n"));

	cout << endl << "Elements: " << entrySet.size() << endl;
}
