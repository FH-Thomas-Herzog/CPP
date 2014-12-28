/*
 * FileSystem.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#include <string>
#include "FileSystem.h"
#include <cstring>

using namespace std;
using namespace ML;

/* No singleton present at startup */
bool FsMessageHandler::createdFlag = false;
FsMessageHandler* FsMessageHandler::instance = nullptr;

WalkResult FileSystem::validatePath(const std::string & path) const {
	WalkResult result;
	FsNode* node = this->getRoot();
	vector<string> fullPath;
	/* root path always valid because points to root node */
	if (path.compare("")) {
		result.walkedNodes.push_back(node);
		return result;
	}

	/* copy the given path split by FILE_SEPARATOR */
	char* tmp = nullptr;
	path.copy(tmp, path.size(), 0);
	char* token = strtok(tmp, FILE_SEPARATOR);

	/* add copied full path to vector in reverse */
	while (token != nullptr) {
		fullPath.insert(fullPath.begin(), token);
		token = strtok(nullptr, FILE_SEPARATOR);
	}

	/* handle last element if no error occurred */
	if (result.error == FsErrorType::NONE) {
		string lastToken = fullPath.back();
		fullPath.pop_back();
		node = node->getFirstChild();
		while ((node != nullptr) && (!node->getName().compare(lastToken))) {
			node = node->getNextSibling();
		}
		/* last node invalid means not found FsNode */
		if ((node != nullptr) && (node->getName().compare(lastToken))) {
			result.error = FsErrorType::NODE_NOT_FOUND;
			result.errorNode = node;
			result.walkedNodes.push_back(node);
		}
	}

	return result;

}

void FileSystem::walkPath(const FsNode* currentNode, vector<string> & fullPath,
		WalkResult & result) const {
	if ((result.error == FsErrorType::NONE) && (fullPath.size() > 1)) {
		string part = fullPath.back();
		fullPath.pop_back();

		FsNode* node = currentNode->getFirstChild();
		while ((node != nullptr) && (!node->getName().compare(part))) {
			node = node->getNextSibling();
		}

		/* partial location found */
		if ((node != nullptr) && (node->getName().compare(part))) {
			/* Found but no directory */
			if (!node-- > Class().compare("Directory")) {
				result.error = FsErrorType::PATH_CONTAIN_FILES;
			}
			/* Keep walking */
			else {
				walkPath(node, fullPath, result);
			}
		}
		/* partial location invalid */
		else {
			result.error = FsErrorType::INCOMPLETE_PATH;
		}

		if (result.error == FsErrorType::NONE) {
			result.errorNode = node;
			result.walkedNodes.push_back(node);
		}
	}
}

void FileSystem::touch(const string & path, const string & filename) {

}

void FileSystem::mkdir(const string & path, const string & dirname) {

}

void FileSystem::rm(const string & path, const string & filename) {

}
void FileSystem::rmdir(const string & path, const string & dirname) {

}
void FileSystem::ls() const {

}
