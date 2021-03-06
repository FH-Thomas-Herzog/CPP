/*
 * FileSystem.cpp
 * The implementation of the FileSystem specification.
 *
 *  Created on: Dec 27, 2014
 *      Author: Thomas Herzog
 */
#include "FileSystem.h"
#include <cstring>

using namespace std;
using namespace ML;

/**
 * No singleton present at startup.
 * Only one single instance needed for the
 */
bool FsErrorHandler::createdFlag = false;
FsErrorHandler* FsErrorHandler::instance = nullptr;

WalkResult FileSystem::validatePath(const std::string & path,
		const std::string childName) const {
	WalkResult result;
	FsNode* node = getRoot();
	vector<string> fullPath;

	result.lastVisitedNode = nullptr;

	/* child name is not supposed to be empty */
	if (childName.empty()) {
		result.error = FsErrorType::INVALID_CHILD;
		return result;
	}

	/* split path and put into vector for later path walking */
	char* buff = strdup(path.c_str());
	char* token = strtok(buff, FILE_SEPARATOR);
	while (token != nullptr) {
		fullPath.insert(fullPath.begin(), token);
		token = strtok(nullptr, FILE_SEPARATOR);
	}

	/* add childname path information if present */
	delete[] buff;
	buff = nullptr;
	buff = strdup(childName.c_str());
	token = strtok(buff, FILE_SEPARATOR);
	char* prevToken = nullptr;
	while (token != nullptr) {
		if (prevToken != nullptr) {
			fullPath.insert(fullPath.begin(), prevToken);
		}
		prevToken = token;
		token = strtok(nullptr, FILE_SEPARATOR);
	}
	/* set actual child name which is always the previous token from the last token */
	result.childNodeName = string(prevToken);

	/* root path always valid because points to root node */
	if ((path.compare("") == 0) && (fullPath.empty())) {
		result.lastVisitedNode = node;
		return result;
	}

	/* walk the path and validate if all of the nodes of the calculated path exist */
	walkPath(node, fullPath, result);

	/* cleanup buffer */
	delete[] buff;

	return result;
} /* FileSystem::validatePath */

void FileSystem::walkPath(const FsNode* currentNode, vector<string> & fullPath,
		WalkResult & result) const {
	/* recursive anchor. only proceed if no error and path information left in vector */
	if ((result.error == FsErrorType::NONE) && (!fullPath.empty())) {
		string part = fullPath.back();
		fullPath.pop_back();

		/* try to get child from current node */
		FsNode* node = getChildByName(currentNode, part);

		/* child node found  */
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
		/* child node not found means path part invalid */
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
	/* find previous from to delete node */
	while ((node != nullptr) && (node != child)) {
		prev = node;
		node = node->getNextSibling();
	}
	/* first child is supposed to be deleted */
	if (prev == nullptr) {
		parent->setFirstChild(node->getNextSibling());
	}
	/* remove child nicely */
	else {
		prev->setNextSibling(node->getNextSibling());
	}
	/* remove reference otherwise would be deleted via cascade */
	node->setNextSibling(nullptr);
	/* delete child */
	delete node;
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
	/* delegate to parent class */
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

FileSystem::~FileSystem() {
} /* FileSystem::~FileSystem */

void FileSystem::touch(const string & path, const string & filename) {
	WalkResult result = validatePath(path, filename);
	/* Error occurred */
	if (result.error != FsErrorType::NONE) {
		string lastNodeName =
				(result.lastVisitedNode != nullptr) ?
						result.lastVisitedNode->getName() : "not available";
		cout << FsErrorHandler::getInstance()->getMessage(result.error)
				<< " (last visited node: " << lastNodeName << ")" << endl
				<< flush;
	}
	/* file exists */
	else if (getChildByName(result.lastVisitedNode, result.childNodeName)
			!= nullptr) {
		cout << "Touch existing file '" << result.childNodeName << "'" << endl
				<< flush;
	}
	/* create new file */
	else {
		insertChild(dynamic_cast<Directory*>(result.lastVisitedNode),
				new File(result.childNodeName));
		cout << "touched newly created file '" << result.childNodeName << "'"
				<< endl << flush;
	}
} /* FileSystem::touch */

void FileSystem::mkdir(const string & path, const string & dirname) {
	WalkResult result = validatePath(path, dirname);
	/* Error occurred */
	if (result.error != FsErrorType::NONE) {
		string lastNodeName =
				(result.lastVisitedNode != nullptr) ?
						result.lastVisitedNode->getName() : "not available";
		cout << FsErrorHandler::getInstance()->getMessage(result.error)
				<< " (last visited node: " << lastNodeName << ")" << endl
				<< flush;
	}
	/* create new directory */
	else {
		insertChild(dynamic_cast<Directory*>(result.lastVisitedNode),
				new Directory(result.childNodeName));
		cout << "directory created '" << result.childNodeName << "'" << endl
				<< flush;
	}
} /* FileSystem::mkdir */

void FileSystem::rm(const string & path, const string & filename) {
	WalkResult result = validatePath(path, filename);
	FsNode* node;
	FsNode* parent;

	/* Error occurred */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	}
	/* try to remove child node */
	else {
		parent = result.lastVisitedNode; //result.walkedNodes.back();
		node = getChildByName(parent, result.childNodeName);
		/* node not found */
		if (node == nullptr) {
			cout << "file not found '" << result.childNodeName << "'" << endl
					<< flush;
		}
		/* node not a file */
		else if (node->Class().compare(FILE_CLASS) != 0) {
			cout << "is not a file '" << result.childNodeName << "'" << endl
					<< flush;
		}
		/* delete file */
		else {
			deleteFsNode(parent, node);
			cout << "file deleted '" << filename << "'" << endl << flush;
		}
	}
} /* FileSystem::rm */

void FileSystem::rmdir(const string & path, const string & dirname) {
	WalkResult result = validatePath(path, dirname);
	FsNode* node;
	FsNode* parent;

	/* Error occurred */
	if (result.error != FsErrorType::NONE) {
		cout << FsErrorHandler::getInstance()->getMessage(result.error) << endl
				<< flush;
	}
	/* try to remove directory */
	else {
		parent = result.lastVisitedNode; //result.walkedNodes.back();
		node = getChildByName(parent, result.childNodeName);
		/* node not found */
		if (node == nullptr) {
			cout << "directory not found '" << result.childNodeName << "'"
					<< endl << flush;
		}
		/* node not a directory */
		else if (!node->Class().compare(DIRECTORY_CLASS) == 0) {
			cout << "is not a directory '" << result.childNodeName << "'"
					<< endl << flush;
		}
		/* directory is not empty */
		else if (node->getFirstChild() != nullptr) {
			cout << "directory is not empty" << endl << flush;
		}
		/* delete directory */
		else {
			deleteFsNode(parent, node);
			cout << "directory deleted '" << result.childNodeName << "'" << endl
					<< flush;
		}
	}
} /* FileSystem::rmdir */

void FileSystem::ls() const {
	print(cout);
} /* FileSystem::ls */
