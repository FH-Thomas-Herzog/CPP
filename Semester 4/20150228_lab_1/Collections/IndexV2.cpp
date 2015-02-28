/*
 * IndexV1.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: cchet
 */
#include "utils.hpp"
#include <fstream>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

void IndexV2(int argc, char** argv) {
	ifstream fis;
	set<string> words;

	openStream(argc, argv, fis);

	transform(istream_iterator<string>(fis), istream_iterator<string>(),
			inserter(words, words.begin()), normalize);

	fis.close();

	copy(words.begin(), words.end(), ostream_iterator<string>(cout, ", "));

	cout << endl << "Elements: " << words.size() << endl;

}
