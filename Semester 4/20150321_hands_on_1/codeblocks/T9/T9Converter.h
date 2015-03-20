/*
 * T9.h
 * This header file specifies the T9 converter and its needed resources
 *
 *  Created on: Mar 6, 2015
 *      Author: Thomas Herzog
 */

#ifndef T9_H_
#define T9_H_

#include <map>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <set>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>
#include <utility>
#include <vector>

/**
 * The sorter class which gets used for sorting strings by their occurrence.
 * This sorter makes only sense when used on a std::map<int, std::unordered_set<std::string>> where the key
 * represents the occurrences and the set the string which have the same occurrence
 */
class StringWordFrequencySorter {
	public:
		inline StringWordFrequencySorter() {
		}

		inline bool operator()(const int& left, const int& right) {
			return left > right;
		}
};

/**
 * This class handles the conversion from and to the T9 specification.
 */
class T9Converter {

	private:
		/* The references to the path of the dictonary */
		std::string& dictonaryPath;
		/* The path to the sample file which provides the occurrence count for the dictonary entries */
		std::string& samplePath;
		/* Map which contains the character mappings to their corresponding T9 value */
		std::tr1::unordered_map<int, std::string> mapping;
		/* Map which contains the character mappings their special characters */
		std::tr1::unordered_map<std::string, std::string> specialCharacterMapping;
		/* The map which represents the index of the dictonary entries (T9Value -> string) */
		std::tr1::unordered_map<long long, std::tr1::unordered_set<std::string>> indexDictonaryT9;
		/* Map which represents the index of the dictonary entries mapped to their length (T9Value length -> map<int, string>)*/
		std::tr1::unordered_map<int,
				std::tr1::unordered_map<long long,
						std::tr1::unordered_set<std::string>>> indexDictonaryT9Length;
		/* The map which represents the index of the dictonary entries mapped to the frequency in the sample file */
		std::tr1::unordered_map<std::string, int> indexDictonaryFrequency;
		/* Set which holds the invalid digits which are not supported by T9 */
		std::tr1::unordered_set<int> unsupportedDigits;
		/* Flag which indicates if a dictonary has been provided */
		bool dictonaryProvided = false;

		/**
		 * Initializes the backed map with the T9 specified character number mapping.
		 */
		void initT9Map();

		/**
		 * Inits the set with the invalid digits which are not supported by T9.
		 */
		void initInvalidDigitsSet();

		/**
		 * Handles the current line of the provided dictonary.
		 *
		 * @param:
		 * 		std::string line: the line to be handled and added to the index(s) if valid.
		 */
		void handleDictonaryEntry(std::string line);

		/**
		 * Converts the given string (single character) to the corresponding digit.
		 *
		 * @param:
		 * 		const std::string c: the string which is allowed to contain only one character.
		 * @return:
		 * 		the T9 representation of the char
		 * @throws:
		 * 		InvalidCharException if the char is not supported by the T9 specification.
		 */
		int string2Digit(const std::string c) const;

		/**
		 * Converts the given single digit to the corresponding character;
		 *
		 * @param:
		 * 		int digit: the digit to be converted to the corresponding character
		 * @return
		 * 		the corresponding character
		 * @throws:
		 * 		InvalidCharException if the given digit is one of the unsupported digits.
		 */
		std::string digit2String(const int digit);

		/**
		 * Loads the sample text provided by the string argument
		 * @param:
		 * 		const:std:string sampleTextPath: the path to the sample file
		 */
		void loadSampleText(const std::string sampleTextPath);

		/**
		 * Normalizes the string by removing all unsupported characters.
		 * @param:
		 * 		const std:string& value: the value to be normalized
		 */
		void normalizeString(std::string& value) const;

		/**
		 * Reloads the dictonary if there is a dictonary path provided.
		 * Does nothing if no dictonary path is present
		 *
		 * @param:
		 * 		std::String dictonaryPath: the path to the dictonary to be loaded.
		 */
		void reloadDictonary(std::string& dictonaryPath);

	public:

		/**
		 * Empty constructor which initializes this handler by initializing the backed T9 map.
		 */
		T9Converter();

		/**
		 * Constructor which gets a dictonary path provided.
		 * This dictonary will be used in stead of the permutation algorithm.
		 *
		 * @param:
		 * 		std::string dictonaryPath: the dictonary path which points
		 * 					to a line separated list of words which can be mapped to the T9 specification.
		 * @param:
		 * 		std::string samplePath: the path to the sample file
		 *
		 */
		T9Converter(std::string dictonaryPath, std::string samplePath);

		/**
		 * For now nothing to do
		 */
		~T9Converter();

		/**
		 * Converts the word to the corresponding T9 representation.
		 *
		 * @param:
		 * 		const string word: the word to be converted
		 * @return:
		 * 		the T9 representation of the word, an thrown exception otherwise
		 * @throws:
		 * 		InvalidCharException if the word contains chars which are supported in the T9 specification.
		 */
		long long word2Number(std::string word) const;

		/**
		 * Converts a T9 number to all of the possible string which are calculated permutations.
		 *
		 * @param:
		 * 		const int number: the T9 number to be converted to the mapped strings
		 * @return:
		 * 		the strings represented by a set which contains all of the mapped strings for the T9 number.
		 */
		std::tr1::unordered_set<std::string> number2Strings(
				const long long value);

		/**
		 * Converts a T9 number to all of the possible string which are provided in the backed directory. (T9 index)
		 *
		 * @param:
		 * 		const int number: the T9 number to be converted to the mapped strings
		 * @return:
		 * 		the strings represented by a set which contains all of the mapped strings for the T9 number.
		 */
		std::tr1::unordered_set<std::string> number2Words(
				const long long value);

		/**
		 * Converts a T9 number to all of the possible string which are provided in the backed directory. (Length index)
		 *
		 * @param:
		 * 		const int number: the T9 number to be converted to the mapped strings
		 * @return:
		 * 		the strings represented by a set which contains all of the mapped strings for the T9 number.
		 */
		std::tr1::unordered_set<std::string> number2WordsByLength(
				const long long value);

		/**
		 * Converts a T9 number to all of the possible string which have length +1 which are provided in the backed directory. (length index)
		 *
		 * @param:
		 * 		const int number: the T9 number to be converted to the mapped strings
		 * @return:
		 * 		the strings represented by a set which contains all of the mapped strings for the T9 number.
		 */
		std::tr1::unordered_set<std::string> numberPrefix2Words(
				const long long value);

		/**
		 * Converts a T9 number to all of the possible string which have length +1 which are provided in the backed directory. (sample index)
		 *
		 * @param:
		 * 		const int number: the T9 number to be converted to the mapped strings
		 * @return:
		 * 		the strings represented by a set which contains all of the mapped strings for the T9 number.
		 */
		std::vector<std::string> numberPrefix2sortedWords(
				const long long value);

		/**
		 * @see T9Converter::reloadDictonary(std:string dictonaryPath)
		 */
		void reloadDictonary();

};

#endif /* T9_H_ */
