/*
 * IndexV5.cpp
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

class WordAdder {
	private:
		wordMap& entries;
		int lineNr;

	public:
		WordAdder(wordMap& entries, int lineNr) :
				entries(entries), lineNr(lineNr) {
		}

		// Funktor
		void operator()(const string word) {
			set<int>& lineNumbers = entries[normalize(word)];
			lineNumbers.insert(lineNr);
		}
};

void IndexV5(int argc, char** argv) {
	wordMap entryMap;
	int curLineNr = 0;

	ifstream fis;
	string line;
	openStream(argc, argv, fis);

	while (fis.good()) {
		curLineNr++;
		getline(fis, line);
		stringstream ss(line);
		for_each(istream_iterator<string>(ss), istream_iterator<string>(),
				// V1 via class
				// WordAdder(entryMap, curLineNr)
				// V2 via lambda expression
				[&entryMap, curLineNr](const string word) {entryMap[normalize(word)].insert(curLineNr);}
				// V3 concise lambda expression (all outer members are accessible via references)
				// [&](const string word) {entryMap[normalize(word)].insert(curLineNr);}
		);
	}

	fis.close();

	for (wordMap::iterator it = entryMap.begin(); it != entryMap.end(); it++) {
		cout << setw(15) << it->first << ": ";
		copy(it->second.begin(), it->second.end(),
				ostream_iterator<int>(cout, ", "));
		cout << endl;
	}

	cout << endl << "Elements: " << entryMap.size() << endl;
}

