/*
 * T9.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: cchet
 */
#include "T9.h"
#include <algorithm>
#include <list>

using namespace std;

// #####################################################################
// T9 Exception implementation
// #####################################################################
InvalidCharException::InvalidCharException(const string errorFunction,
		const char errorChar) :
		errorOperation(errorFunction), errorChar(errorChar) {
}

const char* InvalidCharException::what() const throw () {
	stringstream ss;
	ss << "The char is not supported by T9 !!! operation: '" << errorOperation
			<< "' / error-character: '" << errorChar << "'";
	return ss.str().c_str();
}

InvalidDigitException::InvalidDigitException(const string errorFunction,
		const int errorDigit) :
		errorOperation(errorFunction), errorDigit(errorDigit) {
}

const char* InvalidDigitException::what() const throw () {
	stringstream ss;
	ss << "The char is not supported by T9 !!! operation: '" << errorOperation
			<< "' / error-digit: '" << errorDigit << "'";
	return ss.str().c_str();
}

InvalidConversionException::InvalidConversionException(const string cause,
		const string errorOperation, const string errorString) :
		cause(cause), errorOperation(errorOperation), errorString(errorString) {
}

const char* InvalidConversionException::what() const throw () {
	stringstream ss;
	ss << "Word <-> T9 or visa versa conversion failed !!! "
			<< " / operation: '" << errorOperation << "' / error-string: '"
			<< errorString << "'" << endl << cause << endl;
	return ss.str().c_str();
}

// #####################################################################
// T9 Handler implementation
// #####################################################################
void T9Converter::initT9Map() {
	mapping[2].insert('a');
	mapping[2].insert('b');
	mapping[2].insert('c');

	mapping[3].insert('d');
	mapping[3].insert('e');
	mapping[3].insert('f');

	mapping[4].insert('g');
	mapping[4].insert('h');
	mapping[4].insert('i');

	mapping[5].insert('j');
	mapping[5].insert('k');
	mapping[5].insert('l');

	mapping[6].insert('m');
	mapping[6].insert('n');
	mapping[6].insert('o');

	mapping[7].insert('p');
	mapping[7].insert('q');
	mapping[7].insert('r');
	mapping[7].insert('s');

	mapping[8].insert('t');
	mapping[8].insert('u');
	mapping[8].insert('v');

	mapping[9].insert('w');
	mapping[9].insert('x');
	mapping[9].insert('y');
	mapping[9].insert('z');
}

void T9Converter::initInvalidDigitsSet() {
	invalidDigits.insert(0);
	invalidDigits.insert(1);
}

T9Converter::T9Converter() {
	initT9Map();
	initInvalidDigitsSet();
}

T9Converter::~T9Converter() {
}

int T9Converter::char2Digit(const char c) const throw (InvalidCharException) {
	int t9Value(-1);
	for_each(mapping.begin(), mapping.end(),
			([&c, &t9Value](pair<int, set<char>> mapPair) {
				if(t9Value == -1) {
					auto it = find(mapPair.second.begin(), mapPair.second.end(), c);
					t9Value = (mapPair.second.end() != it) ? mapPair.first : -1;
				}
			}));
	if (t9Value == -1) {
		throw InvalidCharException("int T9Handler::char2Number(const char c)",
				c);
	}
	return t9Value;
}

int T9Converter::word2Number(const string word) const
		throw (InvalidCharException) {
	stringstream ss("");
	try {
		for_each(word.begin(), word.end(), [&ss, this](char c) {
			ss << this->char2Digit(c);
		});
	} catch (InvalidCharException e) {
		throw InvalidConversionException(e.what(),
				"int T9Handler::word2Number(const string word) const throw (InvalidCharException)",
				word);
	}
	return atoi(ss.str().c_str());
}

set<char> T9Converter::digit2CharSet(const int digit) const
		throw (InvalidCharException) {
	// Validate if given parameter is single digit
	if ((digit < 0) || (digit > 9)) {
		throw InvalidDigitException(
				"set<char> T9Converter::digit2CharSet(const int digit) const throw(InvalidCharException)",
				digit);
	}
	// Validate if parameter is supported digit
	auto it = find(invalidDigits.begin(), invalidDigits.end(), digit);
	if (it != invalidDigits.end()) {
		throw InvalidDigitException(
				"set<char> T9Converter::digit2CharSet(const int digit) const throw(InvalidCharException)",
				digit);
	}

	return mapping.at(digit);
}
set<string> T9Converter::number2Word(const int t9Value) const
		throw (InvalidConversionException) {
	set<string> result;
	list<set<char>> usedCharacterList;
	stringstream ss;
	ss << t9Value << '\0';
	string t9ValueString = ss.str();

	// Get character sets for given number
	for_each(t9ValueString.begin(), t9ValueString.end(),
			([&usedCharacterList, this](char c) {
				if(c != '\0') {
					usedCharacterList.push_back(digit2CharSet(((int)c) - 48));
				}}));
	// Iterate over the resulting character sets
	for_each(usedCharacterList.begin(), usedCharacterList.end(),
			([&result](const set<char> characters) {
				set<string> tmp;
				// Iterate over each character of the character set
				for_each(characters.begin(), characters.end(), ([&result, &tmp](const char c) {
									stringstream ss;
									// First time add characters directly to result set
									if(result.empty()) {
										ss << c;
										tmp.insert(ss.str());
									}
									// Each other iteration append each character to each string contained in the result set
									else {
										for_each(result.begin(), result.end(), ([&tmp, &c](const string exisitng) {
															stringstream ss;
															ss << exisitng << c;
															tmp.insert(ss.str());
														}));
									}
								}));
				// Append newly created strings to result set
				result.insert(tmp.begin(), tmp.end());
			}));

	return result;
}
