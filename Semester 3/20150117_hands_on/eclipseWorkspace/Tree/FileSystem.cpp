/*
 * FileSystem.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#include "FileSystem.h"
#include <cstring>

using namespace std;
using namespace ML;

/* No singleton present at startup */
bool FsErrorHandler::createdFlag = false;
FsErrorHandler* FsErrorHandler::instance = nullptr;

WalkResult FileSystem::validatePath(const std::string & path) const {
	WalkResult result;
	FsNode* node = getRoot();
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
		node = getChildByName(node, lastToken);
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

		FsNode* node = getChildByName(node, part);

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

FsNode* FileSystem::getChildByName(const FsNode* node,
		const std::string & name) const {
	FsNode* next = nullptr;
	if (node != nullptr) {
		next = node->getFirstChild();
		while ((next != nullptr) && (!next->getName().compare(name))) {
			next = next->getNextSibling();
		}
		next = ((next != nullptr) && (next->getName().compare(name))) ?
				next : nullptr;
	}
	return next;
}

void FileSystem::touch(const string & path, const string & filename) {
	WalkResult result = validatePath(path);
	/* Path invalid */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	} else {
		FsNode* node = getChildByName(result.walkedNodes.back(), filename);
		if (node == nullptr) {
			insertChild((Directory*) result.walkedNodes.back(),
					new File(filename));
			cout << "touched newly created file '" << filename << "'" << endl
					<< flush;
		} else {
			cout << "touched existing file '" << filename << "'" << endl
					<< flush;
		}
	}
}

void FileSystem::mkdir(const string & path, const string & dirname) {
	WalkResult result = validatePath(path);
	/* Path invalid */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	} else {
		FsNode* node = getChildByName(result.walkedNodes.back(), dirname);
		if (node == nullptr) {
			insertChild((Directory*) result.walkedNodes.back(),
					new Directory(dirname));
			cout << "directory created '" << dirname << "'" << endl << flush;
		} else {
			cout << "directory already exists !!!";
		}
	}
}

void FileSystem::rm(const string & path, const string & filename) {
	WalkResult result = validatePath(path);
	FsNode* prev;
	FsNode* node;
	FsNode* parent;

	/* Path invalid */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	} else {
		parent = result.walkedNodes.back();
		node = getChildByName(parent, filename);
		/* node not found */
		if (node == nullptr) {
			cout << "file not found '" << filename << "'" << endl << flush;
		}
		/* node not a file */
		else if (!node->Class().compare("File")) {
			cout << "is not a directory '" << filename << "'" << endl << flush;
		}
		/* delete file by removing from tree and heap */
		else {
			prev = nullptr;
			node = parent->getFirstChild();
			while ((node != nullptr) && (node->getName().compare(filename))) {
				prev = node;
				node = node->getNextSibling();
			}
			if (prev == nullptr) {
				parent->setFirstChild(node->getNextSibling());
			} else {
				prev->setNextSibling(node->getNextSibling());
			}
			delete node;
		}
	}
}

void FileSystem::rmdir(const string & path, const string & dirname) {

}
void FileSystem::ls() const {

}
