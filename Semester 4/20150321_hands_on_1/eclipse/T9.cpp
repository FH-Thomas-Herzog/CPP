/*
 * T9.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: cchet
 */
#include "T9.h"
#include <algorithm>
#include <list>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

// #####################################################################
// T9 Handler implementation
// #####################################################################
void T9Converter::initT9Map() {
	mapping[0] = "'’"; /* Ignored charactes */
	mapping[2] = "ÅÄäAaàáåâBbCcç";
	mapping[3] = "DdEŒëeéêèœFf";
	mapping[4] = "GgHhIiíî";
	mapping[5] = "JjKkLl";
	mapping[6] = "MmNnñÖöOoôóø";
	mapping[7] = "PpQqRrSsß";
	mapping[8] = "TtUuÜüûúVv";
	mapping[9] = "WwXxYyZz";
}

void T9Converter::initInvalidDigitsSet() {
	invalidDigits.insert(0);
	invalidDigits.insert(1);
}

T9Converter::T9Converter() :
		T9Converter("") {
}

T9Converter::T9Converter(string dictonaryPath) :
		dictonaryPath(dictonaryPath) {
	initT9Map();
	initInvalidDigitsSet();
	reloadDictonary(dictonaryPath);
}

T9Converter::~T9Converter() {
}

int T9Converter::char2Digit(const string c) const throw (InvalidCharException) {
	int t9Value(-1);

	for_each(mapping.begin(), mapping.end(),
			([&c, &t9Value](pair<int, string> mapPair) {
				if(t9Value == -1) {
					int idx = mapPair.second.find(c);
					t9Value = (idx >= 0) ? mapPair.first : -1;
				}
			}));
	if (t9Value == -1) {
		throw InvalidCharException(" [Char Invalid '" + c + "']",
				"int T9Handler::char2Number(const char c)");
	}
	return t9Value;
}

long long T9Converter::word2Number(const string word) const
		throw (InvalidCharException) {
	stringstream ss("");
	try {
		for_each(word.begin(), word.end(), [&ss, this](char c) {
			stringstream tmp;
			tmp << c;
			long long t9Value = this->char2Digit(tmp.str());
			if((t9Value >= 2) && (t9Value <= 9)) {
				ss << t9Value;
			}
		});
	} catch (InvalidCharException e) {
		throw InvalidConversionException("[word invalid '" + word + "']",
				"int T9Handler::word2Number(const string word) const throw (InvalidCharException)",
				e);
	}
	long long result = atol(ss.str().c_str());
//	cout << result << endl;
	return result;
}

string T9Converter::digit2String(const long long digit) const
		throw (InvalidCharException) {
	stringstream ss;
	ss << digit;
	// Validate if given parameter is single digit
	if ((digit < 0) || (digit > 9)) {
		throw InvalidDigitException("[digit invalid '" + ss.str() + "']",
				"set<char> T9Converter::digit2CharSet(const int digit) const throw(InvalidCharException)");
	}
	// Validate if parameter is supported digit
	auto it = find(invalidDigits.begin(), invalidDigits.end(), digit);
	if (it != invalidDigits.end()) {
		throw InvalidDigitException("[digit invalid '" + ss.str() + "']",
				"set<char> T9Converter::digit2CharSet(const int digit) const throw(InvalidCharException)");
	}

	return mapping.at(digit);
}

set<string> T9Converter::number2Strings(const long long t9Value) const
		throw (InvalidConversionException) {

	set<string> result;
	set<string> resultTmp;
	list<string> usedCharacterList;
	stringstream ss;
	ss << t9Value;
	string t9ValueString = ss.str();

// Get character sets for given number
	for_each(t9ValueString.begin(), t9ValueString.end(),
			([&usedCharacterList, this](char c) {
				if(c != '\0') {
					usedCharacterList.push_back(digit2String(((int)c) - 48));
				}}));
// Iterate over the resulting character sets
	for_each(usedCharacterList.begin(), usedCharacterList.end(),
			([&result, &resultTmp, &t9ValueString](const string characters) {
				set<string> tmp;
				// Iterate over each character of the character set
				for_each(characters.begin(), characters.end(), ([&resultTmp, &tmp](const char c) {
									stringstream ss;
									// First time add characters directly to result set
									if(resultTmp.empty()) {
										ss << c;
										tmp.insert(ss.str());
									}
									// Each other iteration append each character to each string contained in the result set
									else {
										for_each(resultTmp.begin(), resultTmp.end(), ([&tmp, &c](const string exisitng) {
															stringstream ss;
															ss << exisitng << c;
															tmp.insert(ss.str());
														}));
									}
								}));
				// Append newly created strings to result set
				for_each(tmp.begin(), tmp.end(), ([&tmp, &result, &resultTmp, &t9ValueString](const string s) {
									if(s.length() == t9ValueString.length()) {
										result.insert(s);
									}
									resultTmp.insert(s);
								}));
			}));

	return result;
}

set<string> T9Converter::number2Words(const long long t9Value)
		throw (InvalidConversionException) {
	map<long long, set<string>>::iterator it = dictonaryIndex.find(t9Value);
	if (it != dictonaryIndex.end()) {
		return dictonaryIndex.at(t9Value);
	} else {
		return set<string>();
	}
}

set<string> T9Converter::number2WordsByLength(const long long t9Value)
		throw (InvalidConversionException) {
	stringstream ss;
	ss << t9Value;
	int length = ss.str().length();
	map<int, map<long long, set<string>>> ::iterator lengthIndexIterator = dictonaryLengthIndex.find(length);
	if (lengthIndexIterator != dictonaryLengthIndex.end()) {
		map<long long, set<string>>::iterator t9ValueIdnexIterator =
				dictonaryLengthIndex.at(length).find(t9Value);
		if (t9ValueIdnexIterator != dictonaryLengthIndex.at(length).end()) {
			return dictonaryLengthIndex.at(length).at(t9Value);
		}
	}

	return set<string>();
}

set<string> T9Converter::numberPrefix2Words(const long long value)
		throw (InvalidConversionException) {
	stringstream ss;
	ss << value;
	set<string> values;

	string valueString = ss.str();
	int length = valueString.length();

	for_each(dictonaryLengthIndex.begin(), dictonaryLengthIndex.end(),
			([&values, &valueString, &length](const pair<int, map<long long, set<string>>> indexEntry) {
				if(indexEntry.first >= length) {
					for_each(indexEntry.second.begin(), indexEntry.second.end(), ([&length, &values, &valueString](const pair<long long, set<string>> entry) {
										stringstream ss;
										ss << entry.first;
										int result = ss.str().find(valueString);
										if(result == 0) {
											values.insert(entry.second.begin(), entry.second.end());
										}
									}));
				}
			}));

	return values;
}

void T9Converter::reloadDictonary() {
	if (dictonaryProvided) {
		reloadDictonary(dictonaryPath);
	}
}

void T9Converter::reloadDictonary(string& dictonaryPath) {
	if (!dictonaryPath.empty()) {
		try {
			ifstream fis;
			fis.open(dictonaryPath.c_str());
			if (fis.fail()) {
				this->dictonaryPath = "";
				dictonaryProvided = false;
				throw DictonaryLoadException(
						"void T9Converter::reloadDictonary() const");
			}

			// Handle line
			string line;
			while ((fis.good()) && (!fis.eof())) {
				getline(fis, line);
				handleDictonaryEntry(line);
			}

			fis.close();
			this->dictonaryProvided = true;

//			for_each(dictonaryIndex.begin(), dictonaryIndex.end(),
//					([](pair<long long, set<string>> p) {
//						cout << endl << p.first << ": ";
//						for_each(p.second.begin(), p.second.end(), ([](string s) {
//											cout << s << ", ";
//										}));
//					}));

//			for_each(dictonaryLengthIndex.begin(), dictonaryLengthIndex.end(),
//					([](pair<int, map<long long, set<string>>> p) {
//						cout << endl << p.first << ": " << endl;
//						for_each(p.second.begin(), p.second.end(), ([](pair<long long, set<string>> s) {
//											cout << ">>>>>" << s.first << ", " << s.second.size() << endl;
//										}));
//					}));
		} catch (exception e) {
			throw DictonaryLoadException(
					"void T9Converter::reloadDictonary(string& dictonaryPath)",
					e);
		}
	}
}

void T9Converter::handleDictonaryEntry(string line) {
	try {
		stringstream ss;
		long long idx = word2Number(line);
		map<long long, set<string>>::iterator itIndex;
		map<int, map<long long, set<string>>> ::iterator itLengthIndex;
		set<string> values;

		/* build index T9Value to set of strings */
		if ((itIndex = dictonaryIndex.find(idx)) != dictonaryIndex.end()) {
			(*itIndex).second.insert(line);
		} else {
			values.insert(line);
			dictonaryIndex.insert(pair<long long, set<string>>(idx, values));
		}

		/* build index length of t9Value to collection of corresponding t9Values to the set of strings */
		ss << idx;
		int length = ss.str().length();
		itLengthIndex = dictonaryLengthIndex.find(length);
		if ((itLengthIndex != dictonaryLengthIndex.end())
				&& (((*itLengthIndex).second.find(idx))
						!= ((*itLengthIndex).second.end()))) {
			(*itLengthIndex).second.at(idx).insert(line);
		} else {
			map<long long, set<string>> indexMap;
			set<string> lengthMappedString;
			lengthMappedString.insert(line);
			pair<long long, set<string>> indexPair(idx, lengthMappedString);

			// When length entry present but no t9Value mapped to any string
			if (itLengthIndex == dictonaryLengthIndex.end()) {
				indexMap.insert(indexPair);
				dictonaryLengthIndex.insert(
						pair<int, map<long long, set<string>>>(length, indexMap));
					} else {
						dictonaryLengthIndex.at(length).insert(indexPair);
					}
				}
			} catch (InvalidConversionException e) {

			}
		}
