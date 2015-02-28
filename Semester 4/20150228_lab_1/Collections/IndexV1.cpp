/*
 * IndexV1.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: cchet
 */
#include "utils.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

void IndexV1(int argc, char** argv) {
	ifstream fis;
	vector<string> words;

	openStream(argc, argv, fis);

	transform(istream_iterator<string>(fis), istream_iterator<string>(),
			back_insert_iterator<vector<string>>(words), normalize);

	fis.close();

	sort(words.begin(), words.end());
	vector<string>::iterator newEnd;
	newEnd = unique(words.begin(), words.end());
	words.erase(newEnd, words.end());

	copy(words.begin(), words.end(), ostream_iterator<string>(cout, ", "));

	cout << endl << "Elements: " << words.size() << endl;

}
