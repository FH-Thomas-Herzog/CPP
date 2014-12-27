/*
 * FileSystem.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Tree.h"
#include "FSNode.h"

class FileSystem: public Tree {
	private:

	public:
		inline FileSystem() :
				Tree::Tree((*new FsNode(""))) {
			Register("FileSystem", "Tree");
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
