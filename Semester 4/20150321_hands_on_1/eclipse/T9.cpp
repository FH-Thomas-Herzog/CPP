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
using namespace std::tr1;

// ############################################################
// Constructor - Destructor section
// ############################################################
T9Converter::T9Converter() :
		T9Converter("", "") {
}

T9Converter::T9Converter(string dictonaryPath, string samplePath) :
		dictonaryPath(dictonaryPath), samplePath(samplePath) {
	initT9Map();
	initInvalidDigitsSet();
	reloadDictonary(dictonaryPath);
	loadSampleText(samplePath);
}

T9Converter::~T9Converter() {
}
// ############################################################
// PRIVATE section
// ############################################################
void T9Converter::initT9Map() {
	mapping[0] = "'’"; /* Ignored charactes */
	mapping[2] = "abc";
	mapping[3] = "def";
	mapping[4] = "ghi";
	mapping[5] = "jkl";
	mapping[6] = "mno";
	mapping[7] = "pqrs";
	mapping[8] = "tuv";
	mapping[9] = "wxyz";

	specialCharacterMapping.insert(pair<string, string>("ÅÄäàáåâ", "a"));
	specialCharacterMapping.insert(pair<string, string>("ç", "c"));
	specialCharacterMapping.insert(pair<string, string>("Œëeéêèœ", "e"));
	specialCharacterMapping.insert(pair<string, string>("íî", "i"));
	specialCharacterMapping.insert(pair<string, string>("ñ", "n"));
	specialCharacterMapping.insert(pair<string, string>("öôóø", "o"));
	specialCharacterMapping.insert(pair<string, string>("Üüûú", "u"));
	specialCharacterMapping.insert(pair<string, string>("ß", "s"));
}

void T9Converter::initInvalidDigitsSet() {
	unsupportedDigits.insert(0);
	unsupportedDigits.insert(1);
}

int T9Converter::string2Digit(const string c) const {
	int t9Value(-1);
	string tmp = c;
	bool replaced = false;

	for_each(specialCharacterMapping.begin(), specialCharacterMapping.end(),
			([&tmp, &replaced](pair<string, string> p) {
				if((!replaced) && (p.first.find(tmp) == 0)) {
					tmp = p.second;
					replaced = true;
				}
			}));
	for_each(mapping.begin(), mapping.end(),
			([&c, &t9Value](pair<int, string> mapPair) {
				if(t9Value == -1) {
					int idx = mapPair.second.find(c);
					t9Value = (idx >= 0) ? mapPair.first : -1;
				}
			}));
	return t9Value;
}

string T9Converter::digit2String(const int digit) {
	stringstream ss;
	ss << digit;
	// Validate if given parameter is single digit
	if ((digit < 0) || (digit > 9)) {
		cout << "Parameter must represent a single digit" << endl << flush;
	}
	// Validate if parameter is supported digit
	auto it = find(unsupportedDigits.begin(), unsupportedDigits.end(), digit);
	if (it != unsupportedDigits.end()) {
		cout << "Invalid digit detected" << endl << flush;
	}

	return mapping[digit];
}

void T9Converter::reloadDictonary() {
	if (dictonaryProvided) {
		reloadDictonary(dictonaryPath);
	}
}

void T9Converter::reloadDictonary(string& dictonaryPath) {
	if (!dictonaryPath.empty()) {
		ifstream fis;
		fis.open(dictonaryPath.c_str());
		if (fis.fail()) {
			this->dictonaryPath = "";
			dictonaryProvided = false;
			cout << "Failed to open the dictonary file" << endl << flush;
		}

		// Handle line
		string line;
		while ((fis.good()) && (!fis.eof())) {
			getline(fis, line);
			normalizeString(line);
			handleDictonaryEntry(line);
		}

		fis.close();
		this->dictonaryProvided = true;
		this->dictonaryPath = string(dictonaryPath);

//			for_each(dictonaryIndex.begin(), dictonaryIndex.end(),
//					([](pair<long long, unordered_set<string>> p) {
//						cout << endl << p.first << ": ";
//						for_each(p.second.begin(), p.second.end(), ([](string s) {
//											cout << s << ", ";
//										}));
//					}));

//			for_each(dictonaryLengthIndex.begin(), dictonaryLengthIndex.end(),
//					([](pair<int, unordered_map<long long, unordered_set<string>>> p) {
//						cout << endl << p.first << ": " << endl;
//						for_each(p.second.begin(), p.second.end(), ([](pair<long long, unordered_set<string>> s) {
//											cout << ">>>>>" << s.first << ", " << s.second.size() << endl;
//										}));
//					}));
	}
}

void T9Converter::handleDictonaryEntry(string line) {
	stringstream ss;
	long long idx = word2Number(line);
	unordered_map<long long, unordered_set<string>>::iterator itIndex;
	unordered_map<int, unordered_map<long long, unordered_set<string>>> ::iterator itLengthIndex;
	unordered_set<string> values;

	/* build index T9Value to unordered_set of strings */
	if ((itIndex = indexDictonaryT9.find(idx)) != indexDictonaryT9.end()) {
		(*itIndex).second.insert(line);
	} else {
		values.insert(line);
		indexDictonaryT9.insert(
				pair<long long, unordered_set<string>>(idx, values));
	}

	/* build index length of t9Value to collection of corresponding t9Values to the unordered_set of strings */
	ss << idx;
	int length = ss.str().length();
	itLengthIndex = indexDictonaryT9Length.find(length);
	if ((itLengthIndex != indexDictonaryT9Length.end())
			&& (((*itLengthIndex).second.find(idx))
					!= ((*itLengthIndex).second.end()))) {
		(*itLengthIndex).second[idx].insert(line);
	} else {
		unordered_map<long long, unordered_set<string>> indexMap;
		unordered_set<string> lengthMappedString;
		lengthMappedString.insert(line);
		pair<long long, unordered_set<string>> indexPair(idx,
				lengthMappedString);

		// When length entry present but no t9Value mapped to any string
		if (itLengthIndex == indexDictonaryT9Length.end()) {
			indexMap.insert(indexPair);
			indexDictonaryT9Length.insert(
					pair<int, unordered_map<long long, unordered_set<string>>>(length, indexMap));
		} else {
			(*itLengthIndex).second.insert(indexPair);
		}
	}

	/* Prepare word frequency unordered_map of the dictonary */
	unordered_map<string, int>::iterator itWordFrequency =
			indexDictonaryFrequency.find(line);
	if (itWordFrequency == indexDictonaryFrequency.end()) {
		indexDictonaryFrequency.insert(pair<string, int>(line, 0));
	}
}

void T9Converter::loadSampleText(const string sampleTextPath) {
	if (!sampleTextPath.empty()) {
		vector<string> words;
		ifstream fis;
		fis.open(sampleTextPath.c_str());
		if (fis.fail()) {
			cout << "Failed to open the sampel file" << endl << flush;
		}

		// Handle line
		for_each(istream_iterator<string>(fis), istream_iterator<string>(),
				([this](string word) {
					normalizeString(word);
					unordered_map<string, int>::iterator it = indexDictonaryFrequency.find(word);
					if(it != indexDictonaryFrequency.end()) {
						(*it).second++;
					}
				}));

		fis.close();

//			for_each(wordFrequencyMap.begin(), wordFrequencyMap.end(),
//					([](pair<string, int> p) {
//						cout << p.first << ": " << p.second << endl;
//					}));
	}
}

void T9Converter::normalizeString(std::string& word) const {
	string::iterator newEnd;
	newEnd = remove_if(word.begin(), word.end(), ([](const char ch) {
		return static_cast<bool>(ispunct(ch));
	}));
	newEnd = remove_if(word.begin(), newEnd, ([](const char ch) {
		return static_cast<bool>(isdigit(ch));
	}));
	word.erase(newEnd, word.end());
	transform(word.begin(), word.end(), word.begin(), ([](const char ch) {
		return static_cast<char>(tolower(ch));
	}));
}

// ############################################################
// PUBLIC section
// ############################################################
long long T9Converter::word2Number(const string word) const {
	stringstream ss("");
	for_each(word.begin(), word.end(), [&ss, this](char c) {
		stringstream tmp;
		tmp << c;
		long long t9Value = this->string2Digit(tmp.str());
		if((t9Value >= 2) && (t9Value <= 9)) {
			ss << t9Value;
		}
	});
	string res = ss.str();
	if (res.empty()) {
		return -1;
	} else {
		return atol(ss.str().c_str());
	}
}

unordered_set<string> T9Converter::number2Strings(const long long t9Value) {

	unordered_set<string> result;
	unordered_set<string> resultTmp;
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
				unordered_set<string> tmp;
				// Iterate over each character of the character unordered_set
				for_each(characters.begin(), characters.end(), ([&resultTmp, &tmp](const char c) {
									stringstream ss;
									// First time add characters directly to result unordered_set
									if(resultTmp.empty()) {
										ss << c;
										tmp.insert(ss.str());
									}
									// Each other iteration append each character to each string contained in the result unordered_set
									else {
										for_each(resultTmp.begin(), resultTmp.end(), ([&tmp, &c](const string exisitng) {
															stringstream ss;
															ss << exisitng << c;
															tmp.insert(ss.str());
														}));
									}
								}));
				// Append newly created strings to result unordered_set
				for_each(tmp.begin(), tmp.end(), ([&tmp, &result, &resultTmp, &t9ValueString](const string s) {
									if(s.length() == t9ValueString.length()) {
										result.insert(s);
									}
									resultTmp.insert(s);
								}));
			}));

	return result;
}

unordered_set<string> T9Converter::number2Words(const long long t9Value) {
	unordered_map<long long, unordered_set<string>>::iterator it =
			indexDictonaryT9.find(t9Value);
	if (it != indexDictonaryT9.end()) {
		return (*it).second;
	} else {
		return unordered_set<string>();
	}
}

unordered_set<string> T9Converter::number2WordsByLength(
		const long long t9Value) {
	stringstream ss;
	ss << t9Value;
	int length = ss.str().length();
	unordered_map<int, unordered_map<long long, unordered_set<string>>> ::iterator lengthIndexIterator = indexDictonaryT9Length.find(length);
	if (lengthIndexIterator != indexDictonaryT9Length.end()) {
		unordered_map<long long, unordered_set<string>>::iterator t9ValueIdnexIterator =
				(*lengthIndexIterator).second.find(t9Value);
		if (t9ValueIdnexIterator != indexDictonaryT9Length[length].end()) {
			return (*t9ValueIdnexIterator).second;
		}
	}

	return unordered_set<string>();
}

unordered_set<string> T9Converter::numberPrefix2Words(const long long value) {
	stringstream ss;
	ss << value;
	unordered_set<string> values;

	string valueString = ss.str();
	int length = valueString.length();

	for_each(indexDictonaryT9Length.begin(), indexDictonaryT9Length.end(),
			([&values, &valueString, &length](const pair<int, unordered_map<long long, unordered_set<string>>> indexEntry) {
				if(indexEntry.first >= length) {
					for_each(indexEntry.second.begin(), indexEntry.second.end(), ([&length, &values, &valueString](const pair<long long, unordered_set<string>> entry) {
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

vector<string> T9Converter::numberPrefix2sortedWords(const long long value) {
	stringstream ss;
	ss << value;
	string valueString = ss.str();
	vector<string> result;

	/* get dictonary result */
	unordered_set<string> values = numberPrefix2Words(value);
	map<int, vector<string>, StringWordFrequencySorter> tmpMap;

	for_each(values.begin(), values.end(),
			([this, &tmpMap](const string stringValue) {
				unordered_map<string, int>::iterator it = indexDictonaryFrequency.find(stringValue);
				if(it != indexDictonaryFrequency.end()) {
					map<int, vector<string>, StringWordFrequencySorter>::iterator itTmpMap = tmpMap.find((*it).second);
					if(itTmpMap != tmpMap.end()) {
						(*itTmpMap).second.push_back(stringValue);
					} else {
						vector<string> tmpSet;
						tmpSet.push_back(stringValue);
						tmpMap.insert(pair<int, vector<string>>((*it).second, tmpSet));
					}
				}
			}));

	for_each(tmpMap.begin(), tmpMap.end(),
			([&result](pair<int, vector<string>> mapPair) {
				for_each(mapPair.second.begin(), mapPair.second.end(), ([&result](const string val) {
									result.push_back(val);
								}));
			}));

	return result;

}

