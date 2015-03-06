/*
 * T9.h
 *
 *  Created on: Mar 6, 2015
 *      Author: cchet
 */

#ifndef T9_H_
#define T9_H_

#include <map>
#include <set>
#include <string>
#include <sstream>
#include <exception>

/**
 * The exception which indicates that the char is not supported by the T9 specification.
 */
class InvalidCharException: public std::exception {
	private:
		const std::string errorOperation;
		const char errorChar;
	public:
		InvalidCharException() = delete;
		InvalidCharException(const std::string errorFunction,
				const char errorChar);

		const char* what() const throw ();
};

/**
 * The exception which indicates that the integer is not supported by the T9 specification.
 */
class InvalidDigitException: public std::exception {
	private:
		const std::string errorOperation;
		const int errorDigit;
	public:
		InvalidDigitException() = delete;
		InvalidDigitException(const std::string errorFunction,
				const int errorDigit);

		const char* what() const throw ();
};

/**
 * The exception which indicates that the conversion failed for any reason.
 */
class InvalidConversionException: public std::exception {
	private:
		const std::string cause;
		const std::string errorOperation;
		const std::string errorString;
	public:
		InvalidConversionException() = delete;
		InvalidConversionException(const std::string cause,
				const std::string errorFunction, const std::string errorString);

		const char* what() const throw ();
};

/**
 * This class handles the conversion from and to the T9 specification.
 */
class T9Converter {
	private:
		std::map<int, std::set<char>> mapping;
		std::set<int> invalidDigits;

		/**
		 * Initializes the backed map with the T9 specified character number mapping.
		 */
		void initT9Map();

		/**
		 * Inits the set with the invalid digits which are not supported by T9.
		 */
		void initInvalidDigitsSet();

	public:

		/**
		 * Empty constructor which initializes this handler by initializing the backed T9 map.
		 */
		T9Converter();

		/**
		 * For no nothing to do
		 */
		~T9Converter();

		/**
		 * Converts the given char to the corresponding digit.
		 *
		 * @param:
		 * 		const char c: the char to be converted to the mapped integer value.
		 * @return:
		 * 		the T9 representation of the char
		 * @throws:
		 * 		InvalidCharException if the char is not supported by the T9 specification.
		 */
		int char2Digit(const char c) const throw (InvalidCharException);

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
		int word2Number(const std::string word) const
				throw (InvalidCharException);

		/**
		 * Converts the given single digit to the corresponding character;
		 *
		 * @param:
		 * 		const int digit: the digit to be converted to the corresponding character
		 * @return
		 * 		the corresponding character
		 * @throws:
		 * 		InvalidCharException if the given digit is one of the unsupported digits.
		 */
		std::set<char> digit2CharSet(const int digit) const throw (InvalidCharException);

		/**
		 * Converts a T9 number to all of the possible string which are provided in the backed directory.
		 *
		 * @param:
		 * 		const int number: the T9 number to be converted to the mapped strings
		 * @return:
		 * 		the strings represented by a set which contains all of the mapped strings for the T9 number.
		 * @thorws:
		 * 		InvalidConversionException if the number contains invalid digits. (0, 1 are not supported by T9)
		 */
		std::set<std::string> number2Word(const int) const
				throw (InvalidConversionException);
};

#endif /* T9_H_ */
