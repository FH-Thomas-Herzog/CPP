/*
 * FsMessageHandler.h
 * This is the specification and implementation of the FsErrorHandler.
 * This class is implemented with the Singleton Pattern
 *
 *  Created on: Dec 28, 2014
 *      Author: Thomas Herzog
 */

#ifndef FSMESSAGEHANDLER_H_
#define FSMESSAGEHANDLER_H_

#include <map>
#include <string>
#include <sstream>

/**
 * This enumeration class holds all possible errors which can occur on the file system
 */
enum class FsErrorType {
	/* No error occurred */
	NONE,
	/* Given path contains files which cannot be walked as directories */
	PATH_CONTAIN_FILES = 1,
	/* Path contains directories which do not exist */
	INVALID_PATH = 2,
	/* File does not exist under intended location */
	FILE_NOT_FOUND = 3,
	/* directory does not exist under intended location */
	DIR_NOT_FOUND = 4,
	/* directory is not empty and therefore cannot be deleted */
	DIR_NOT_EMPTY = 5,
	/* not found directory/file */
	NODE_NOT_FOUND = 6,
	/* Child name is invalid */
	INVALID_CHILD = 7
};

/**
 * Singleton error message handler which provides the error messages for the specified errors.
 * It gets constructed during first call of getInstance and destroyed when program shuts down
 */
class FsErrorHandler {

private:
	static bool createdFlag;
	static FsErrorHandler* instance;
	std::map<FsErrorType, std::string> errorMessages;

	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	/**
	 * Private constructor because not allowed to be constructed via new operator.
	 * Init the message during construction
	 */
	inline FsErrorHandler() {
		initMessages();
	}

	/**
	 * Prevent destruction of FsErrorHandler singleton pointer.
	 */
	inline ~FsErrorHandler() {
	}

	/**
	 * Initializes the message map by putting all messages into a map to their corresponding enumeration.
	 */
	inline void initMessages() {
		errorMessages.insert(
				std::pair<FsErrorType, std::string>(FsErrorType::DIR_NOT_EMPTY,
						"Cannot delete not empty directory"));
		errorMessages.insert(
				std::pair<FsErrorType, std::string>(FsErrorType::DIR_NOT_FOUND,
						"Directory not found"));
		errorMessages.insert(
				std::pair<FsErrorType, std::string>(FsErrorType::FILE_NOT_FOUND,
						"File not found"));
		errorMessages.insert(
				std::pair<FsErrorType, std::string>(FsErrorType::INVALID_PATH,
						"Given path is invalid !!!"));
		errorMessages.insert(
				std::pair<FsErrorType, std::string>(
						FsErrorType::PATH_CONTAIN_FILES,
						"Cannot walk path which contains files"));
		errorMessages.insert(
				std::pair<FsErrorType, std::string>(FsErrorType::INVALID_CHILD,
						"Child name is invalid"));
	}

public:
	/**
	 * Returns the existing instance or creates a new instance
	 * if the instance is not present yet.
	 *
	 * @return
	 * 		the created singleton instance
	 */
	static inline FsErrorHandler* getInstance() {
		if (!createdFlag) {
			std::cout << "singleton instance created" << std::endl
					<< std::flush;
			instance = new FsErrorHandler();
			createdFlag = true;
			return instance;
		} else {
			std::cout << "returning existing singleton instance" << std::endl
					<< std::flush;
			return instance;
		}
	}

	/**
	 * Allows to nicely destroy the singleton instance.
	 */
	static inline void destroyInstance() {
		if (createdFlag) {
			delete instance;
			createdFlag = false;
			std::cout << "singleton instance destroyed" << std::endl
					<< std::flush;
		} else {
			std::cout << "no singleton instance present for destroy "
					<< std::endl << std::flush;
		}
	}

	/**
	 * Returns the message mapped to the given enum.
	 *
	 * @param:
	 * 		type: the error type mapped to a error message
	 * @return
	 * 		the mapped message or a message which tells the caller that this key is not mapped
	 * 		to any message
	 */
	inline std::string getMessage(const FsErrorType & type) {
		try {
			return errorMessages.at(type);
		} catch (std::out_of_range & e) {
			std::stringstream ss;
			ss << "Key not managed by this handler !!!" << std::endl << e.what()
					<< std::endl << std::flush;
			return ss.str();
		}
	}
};

#endif /* FSMESSAGEHANDLER_H_ */
