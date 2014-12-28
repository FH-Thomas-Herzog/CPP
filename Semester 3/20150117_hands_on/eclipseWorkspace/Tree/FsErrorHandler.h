/*
 * FsMessageHandler.h
 *
 *  Created on: Dec 28, 2014
 *      Author: cchet
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
	INCOMPLETE_PATH = 2,
	/* File does not exist under intended location */
	FILE_NOT_FOUND = 3,
	/* directory does not exist under intended location */
	DIR_NOT_FOUND = 4,
	/* directory is not empty and therefore cannot be deleted */
	DIR_NOT_EMPTY = 5,
	/* not found directory/file */
	NODE_NOT_FOUND = 6
};

/**
 * Singleton error message handler which provides the error messages for the specified errors.
 */
class FsMessageHandler {
	private:
		static bool createdFlag;
		static FsMessageHandler* instance;
		std::map<FsErrorType, std::string> errorMessages;

		inline FsMessageHandler() {
		}
		inline FsMessageHandler(const FsMessageHandler & other) {
		}
		inline FsMessageHandler & operator =(const FsMessageHandler & other) {
		}

		inline void initMessages() {
			errorMessages.insert(
					std::pair<FsErrorType, std::string>(
							FsErrorType::DIR_NOT_EMPTY,
							"Cannot delete not empty directory"));
			errorMessages.insert(
					std::pair<FsErrorType, std::string>(
							FsErrorType::DIR_NOT_FOUND, "Directory not found"));
			errorMessages.insert(
					std::pair<FsErrorType, std::string>(
							FsErrorType::FILE_NOT_FOUND, "File not found"));
			errorMessages.insert(
					std::pair<FsErrorType, std::string>(
							FsErrorType::INCOMPLETE_PATH,
							"Cannot walk incomplete path"));
			errorMessages.insert(
					std::pair<FsErrorType, std::string>(
							FsErrorType::PATH_CONTAIN_FILES,
							"Cannot walk path which contains files"));
		}
	public:
		~FsMessageHandler() {
			createdFlag = false;
			instance = nullptr;
		}

		static inline FsMessageHandler* getInstance() {
			if (!createdFlag) {
				instance = new FsMessageHandler();
				createdFlag = true;
				return instance;
			} else {
				return instance;
			}
		}

		inline std::string getMessage(const FsErrorType & type) {
			try {
				return errorMessages.at(type);
			} catch (std::out_of_range & e) {
				std::stringstream ss;
				ss << "Key not managed by this handler !!!" << std::endl
						<< e.what() << std::endl << std::flush;
				return ss.str();
			}
		}
};

#endif /* FSMESSAGEHANDLER_H_ */
