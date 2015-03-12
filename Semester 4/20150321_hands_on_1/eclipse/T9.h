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
#include <fstream>

class BaseT9exception: public std::exception {
	protected:
		std::exception &cause;
		const std::string message;
		const std::string errorOperation;

	public:
		inline BaseT9exception() :
				message(""), cause(*this), errorOperation("") {
		}

		inline BaseT9exception(const std::string message,
				const std::string errorOperation) :
				BaseT9exception(message, errorOperation, *this) {
		}

		inline BaseT9exception(const std::string message,
				const std::string errorOperation, std::exception& cause) :
				message(message), errorOperation(errorOperation), cause(cause) {
		}

		virtual inline const char* what() const throw () {
			std::stringstream ss;
			ss << message << " | operation: " << errorOperation << std::endl;
			if ((dynamic_cast<BaseT9exception*>(&cause)) != nullptr) {
				ss << std::endl << "[cause] " << cause.what() << std::endl;
			}
			return ss.str().c_str();
		}
};
/**
 * The exception which indicates that the char is not supported by the T9 specification.
 */
class InvalidCharException: public BaseT9exception {
	public:
		InvalidCharException() = delete;
		inline InvalidCharException(const std::string message,
				const std::string errorOperation) :
				BaseT9exception(
						"The char is not supported by T9 !!! " + message,
						errorOperation) {
		}
};

/**
 * The exception which indicates that the integer is not supported by the T9 specification.
 */
class InvalidDigitException: public BaseT9exception {
	public:
		InvalidDigitException() = delete;
		inline InvalidDigitException(const std::string message,
				const std::string errorOperation) :
				BaseT9exception(
						"The digit is not supported by T9 !!! " + message,
						errorOperation) {
		}
};

/**
 * The exception which indicates that the conversion failed for any reason.
 */
class InvalidConversionException: public BaseT9exception {
	public:
		InvalidConversionException() = delete;
		inline InvalidConversionException(const std::string message,
				const std::string errorOperation, std::exception& cause) :
				BaseT9exception(
						"Word <-> T9 or visa versa conversion failed !!! "
								+ message, errorOperation, cause) {
		}
};

/**
 * The exception which indicates that the conversion failed for any reason.
 */
class DictonaryLoadException: public BaseT9exception {
	public:
		DictonaryLoadException() = delete;
		inline DictonaryLoadException(const std::string errorOperation) :
				BaseT9exception("Dictonary could not be loaded !!!",
						errorOperation) {
		}
		inline DictonaryLoadException(const std::string errorOperation,
				std::exception& cause) :
				BaseT9exception("Dictonary could not be loaded !!!",
						errorOperation, cause) {
		}
};

/**
 * This class handles the conversion from and to the T9 specification.
 */
class T9Converter {
	private:
		bool dictonaryProvided = false;
		std::string& dictonaryPath;
		std::map<int, std::string> mapping;
		std::map<long long, std::set<std::string>> dictonaryIndex;
		std::map<int, std::map<long long, std::set<std::string>>> dictonaryLengthIndex;
		std::set<int> invalidDigits;

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
		 * If the line represents a valid word entry the line will be added,
		 * otherwise the line will be ignored.
		 *
		 * @param:
		 * 		std::String line: the line to be handled and added to the index if valid.
		 */
		void handleDictonaryEntry(std::string line);

		/**
		 * Converts the given char to the corresponding digit.
		 *
		 * @param:
		 * 		const std::string c: the string which is allowed to contain only one character.
		 * @return:
		 * 		the T9 representation of the char
		 * @throws:
		 * 		InvalidCharException if the char is not supported by the T9 specification.
		 */
		int char2Digit(const std::string c) const throw (InvalidCharException);

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
		std::string digit2String(const long long digit) const
				throw (InvalidCharException);


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
		 * 		const std::String dictonaryPath: the dictonary path which points
		 * 					to a line separated list of words which can be mapped to the T9 specification.
		 */
		T9Converter(std::string dictonaryPath);

		/**
		 * For no nothing to do
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
		long long word2Number(const std::string word) const
				throw (InvalidCharException);

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
		std::set<std::string> number2Strings(const long long value) const
				throw (InvalidConversionException);

		std::set<std::string> number2Words(const long long value)
				throw (InvalidConversionException);

		std::set<std::string> number2WordsByLength(const long long value)
				throw (InvalidConversionException);

		std::set<std::string> numberPrefix2Words(const long long value)
				throw (InvalidConversionException);
		/**
		 * @see T9Converter::reloadDictonary(std:string dictonaryPath)
		 */
		void reloadDictonary();

		/**
		 * Reloads the dictonary if there is a dictonary path provided.
		 * Does nothing if no dictonary path is present
		 *
		 * @param:
		 * 		std::String dictonaryPath: the path to the dictonary to be loaded.
		 */
		void reloadDictonary(std::string& dictonaryPath);
};

#endif /* T9_H_ */
