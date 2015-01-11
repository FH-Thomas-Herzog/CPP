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
	if (path.compare("") == 0) {
		result.lastVisitedNode = node;
		return result;
	}

	result.lastVisitedNode = nullptr;

	/* copy the given path split by FILE_SEPARATOR */
	char* tmp = new char[path.size()];
	strncpy(tmp, path.c_str(), path.size());
	tmp[path.size()] = '\0';
	char* token = strtok(tmp, FILE_SEPARATOR);

	/* add copied full path to vector in reverse */
	while (token != nullptr) {
		fullPath.insert(fullPath.begin(), token);
		token = strtok(nullptr, FILE_SEPARATOR);
	}

	/* walk the path and validate if all of the node exist */
	walkPath(node, fullPath, result);

	/* clean up */
	delete tmp;

	return result;
} /* FileSystem::validatePath */

void FileSystem::walkPath(const FsNode* currentNode, vector<string> & fullPath,
		WalkResult & result) const {
	if ((result.error == FsErrorType::NONE) && (!fullPath.empty())) {
		string part = fullPath.back();
		fullPath.pop_back();

		FsNode* node = getChildByName(currentNode, part);

		/* partial location found */
		if (node != nullptr) {
			result.lastVisitedNode = node;
			/* Found but no directory */
			if (!node->Class().compare(DIRECTORY_CLASS) == 0) {
				result.error = FsErrorType::PATH_CONTAIN_FILES;
			}
			/* Keep walking */
			else {
				walkPath(node, fullPath, result);
			}
		}
		/* path invalid */
		else {
			result.error = FsErrorType::INVALID_PATH;
		}
	}
} /* FileSystem::walkPath */

FsNode* FileSystem::getChildByName(const FsNode* node,
		const std::string & name) const {
	FsNode* next = nullptr;
	if (node != nullptr) {
		next = node->getFirstChild();
		while ((next != nullptr) && (!next->getName().compare(name) == 0)) {
			next = next->getNextSibling();
		}
		next = ((next != nullptr) && (next->getName().compare(name) == 0)) ?
				next : nullptr;
	}
	return next;
} /* FileSystem::getChildByName */

void FileSystem::deleteFsNode(FsNode* parent, FsNode* child) {
	FsNode* prev = nullptr;
	FsNode* node = parent->getFirstChild();
	/* get previous from child sibling */
	while ((node != nullptr) && (node != child)) {
		prev = node;
		node = node->getNextSibling();
	}
	/* first child is supposed to be deleted */
	if (prev == nullptr) {
		parent->setFirstChild(node->getNextSibling());
	}
	/* remove child safely */
	else {
		prev->setNextSibling(node->getNextSibling());
	}
	/* delete child */
	delete child;
} /* FileSystem::deleteFsNode */

void FileSystem::deleteSubTree(FsNode* node) {
	/* delegate to parent class */
	Tree::deleteSubTree(node);
} /* FileSystem::deleteSubTree */

void FileSystem::setRoot(Directory* node) {
	// FileSystem root cannot be defined from caller is always root path ""
	std::cout << "Root is not allowed to be set on a FileSystem instance !!! "
			<< std::endl << std::flush;
} /* FileSystem::setRoot */

void FileSystem::insertChild(Directory* parent, FsNode* child) {
	/* delegate to parent child class */
	Tree::insertChild(parent, child);
} /* FileSystem::insertChild */

Directory* FileSystem::getRoot() const {
	/* it safe to cast brutally because can only be instanceof Directory */
	return (Directory*) Tree::getRoot();
} /* FileSystem::getRoot */

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
FileSystem::FileSystem() :
		Tree::Tree(new Directory("")) {
	Register(FILESYSTEM_CLASS, TREE_CLASS);
} /* FileSystem::FileSystem */

FileSystem::FileSystem(const FileSystem & other) :
		Tree::Tree(other) {
	Register(FILESYSTEM_CLASS, TREE_CLASS);
} /* FileSystem::FileSystem */

void FileSystem::touch(const string & path, const string & filename) {
	WalkResult result = validatePath(path);
	/* Error occured */
	if (result.error != FsErrorType::NONE) {
		string lastNodeName =
				(result.lastVisitedNode != nullptr) ?
						result.lastVisitedNode->getName() : "not available";
		cout << FsErrorHandler::getInstance()->getMessage(result.error)
				<< " (last visited node: " << lastNodeName << ")" << endl
				<< flush;
	}
	/* if file exists */
	else if (getChildByName(result.lastVisitedNode, filename) != nullptr) {
		cout << "Touch existing file '" << filename << "'" << endl << flush;
	}
	/* create new file */
	else {
		insertChild(dynamic_cast<Directory*>(result.lastVisitedNode),
				new File(filename));
		cout << "touched newly created file '" << filename << "'" << endl
				<< flush;
	}
} /* FileSystem::touch */

void FileSystem::mkdir(const string & path, const string & dirname) {
	WalkResult result = validatePath(path);
	/* Path invalid */
	if (result.error != FsErrorType::NONE) {
		string lastNodeName =
				(result.lastVisitedNode != nullptr) ?
						result.lastVisitedNode->getName() : "not available";
		cout << FsErrorHandler::getInstance()->getMessage(result.error)
				<< " (last visited node: " << lastNodeName << ")" << endl
				<< flush;
	} else {
		insertChild(dynamic_cast<Directory*>(result.lastVisitedNode),
				new Directory(dirname));
		cout << "directory created '" << dirname << "'" << endl << flush;
	}
} /* FileSystem::mkdir */

void FileSystem::rm(const string & path, const string & filename) {
	WalkResult result = validatePath(path);
	FsNode* node;
	FsNode* parent;

	/* Path invalid */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	} else {
		parent = result.lastVisitedNode; //result.walkedNodes.back();
		node = getChildByName(parent, filename);
		/* node not found */
		if (node == nullptr) {
			cout << "file not found '" << filename << "'" << endl << flush;
		}
		/* node not a file */
		else if (!node->Class().compare(FILE_CLASS) == 0) {
			cout << "is not a file '" << filename << "'" << endl << flush;
		}
		/* delete file by removing from tree and heap */
		else {
			deleteFsNode(parent, node);
		}
	}
} /* FileSystem::rm */

void FileSystem::rmdir(const string & path, const string & dirname) {
	WalkResult result = validatePath(path);
	FsNode* node;
	FsNode* parent;

	/* Path invalid */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	} else {
		parent = result.lastVisitedNode; //result.walkedNodes.back();
		node = getChildByName(parent, dirname);
		/* node not found */
		if (node == nullptr) {
			cout << "directory not found '" << dirname << "'" << endl << flush;
		}
		/* node not a file */
		else if (!node->Class().compare(DIRECTORY_CLASS) == 0) {
			cout << "is not a directory '" << dirname << "'" << endl << flush;
		}
		/* delete file by removing from tree and heap */
		else {
			deleteFsNode(parent, node);
		}
	}
} /* FileSystem::rmdir */

void FileSystem::ls() const {
	print(cout);
} /* FileSystem::ls */
