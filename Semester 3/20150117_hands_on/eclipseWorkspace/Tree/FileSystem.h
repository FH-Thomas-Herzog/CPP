/*
 * FileSystem.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <vector>
#include <string>
#include "Tree.h"
#include "FSNode.h"
#include "File.h"
#include "Directory.h"
#include "FsErrorHandler.h"

#ifdef _WIN32
#define FILE_SEPARATOR   "\\"
#else
#define FILE_SEPARATOR   "/"
#endif

/**
 * This struct is used to hold information about the walked path.
 */
typedef struct WalkResult {
		FsErrorType error = FsErrorType::NONE;
		FsNode* errorNode = nullptr;
		std::vector<FsNode*> walkedNodes;
} WalkResult;

/**
 * This class represents a Tree implementation which realizes a file system.
 * Therefore that some formerly public visible methods are not allowed to be called
 * by an outside caller, they have been moved to the private section to avoid file system manipulation
 * by the caller outside the newly introduced methods such as mkdir and so on.
 *
 * Therefore that Tree implementation only depends on Node types but this implementations differs between
 * Directory (FsNode) and File(FsNode) where FsNode inherits from Node some methods where overwritten
 * to restrict the the types which must be given by the caller.
 * For instance it is not possible to add a child to a File node, which leads to the fact
 * that only directories are valid parents for inserted Nodes.
 */
class FileSystem: public Tree {
	private:
		////////////////////////////////////////////////////////////
		// private utils                                          //
		////////////////////////////////////////////////////////////
		WalkResult validatePath(const std::string & path) const;

		void walkPath(const FsNode* currentNode,
				std::vector<std::string> & fullPath, WalkResult & result) const;

		FsNode* getChildByName(const FsNode* node, const std::string & name) const;

		////////////////////////////////////////////////////////////
		// hidden former public methods                           //
		// for type safety (Node* -> Directory*)                  //
		// not allowed to be called by outside caller             //
		////////////////////////////////////////////////////////////
		virtual inline void deleteSubTree(FsNode* node) {
			Tree::deleteSubTree(node);
		}

		virtual inline void setRoot(Directory* node) {
			// FileSystem root cannot be defined from caller is always root path ""
			std::cout
					<< "Root is not allowed to be set on a FileSystem instance !!! "
					<< std::endl << std::flush;
		}

		virtual inline void insertChild(Directory* parent, FsNode* child) {
			Tree::insertChild(parent, child);
		}

		virtual inline FsNode* getRoot() const {
			return (FsNode*) Tree::getRoot();
		}

	public:
		inline FileSystem() :
				Tree::Tree((*new FsNode(""))) {
			Register("FileSystem", "Tree");
		}

		inline FileSystem(const FileSystem & other) :
				Tree::Tree(other) {
			/* Only register if other is instance of FileSystem */
			if (other.Class().compare("FileSystem")) {
				Register("FileSystem", "Tree");
			}
		}

		virtual void touch(const std::string & path,
				const std::string & filename);

		virtual void mkdir(const std::string & path,
				const std::string & dirname);

		virtual void rm(const std::string & path, const std::string & filename);

		virtual void rmdir(const std::string & path,
				const std::string & dirname);

		virtual void ls() const;
};

#endif /* FILESYSTEM_H_ */
