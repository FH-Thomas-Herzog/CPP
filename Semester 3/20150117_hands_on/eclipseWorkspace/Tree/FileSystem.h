/*
 * FileSystem.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <vector>
#include "Tree.h"
#include "FSNode.h"
#include "Directory.h"
#include "FsErrorHandler.h"

#ifdef _WIN32
#define FILE_SEPARATOR   "\\"
#else
#define FILE_SEPARATOR   "/"
#endif

typedef struct WalkResult {
		FsErrorType error = FsErrorType::NONE;
		FsNode* errorNode = nullptr;
		std::vector<FsNode*> walkedNodes;
} WalkResult;

class FileSystem: public Tree {
	private:
		WalkResult validatePath(const std::string & path) const;

		void walkPath(const FsNode* currentNode,
				std::vector<std::string> & fullPath, WalkResult & result) const;

		// Moved to private section to hide methods from caller
		virtual inline void deleteSubTree(Directory* node) {
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

	public:
		inline FileSystem() :
				Tree::Tree((*new FsNode(""))) {
			Register("FileSystem", "Tree");
		}

		inline FileSystem(const FileSystem & other) :
				Tree::Tree(other) {
			/* Only register if other is instance of Tree */
			if (other.Class().compare("FileSystem")) {
				Register("FileSystem", "Tree");
			}
		}

		virtual inline FsNode* getRoot() const {
			return (FsNode*) Tree::getRoot();
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
