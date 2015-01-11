/*
 * Directory.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "FSNode.h"

#define DIRECTORY_CLASS "Directory"

class Directory: public FsNode {
	private:

	public:

		Directory() = delete;

		Directory(const std::string & name);

		Directory(const Directory & other);

		virtual ~Directory();

		virtual Directory* clone() const;

		virtual std::string AsString() const;

		////////////////////////////////////////////////////////////
		// Utils                                                  //
		////////////////////////////////////////////////////////////
		/**
		 * Prints the directory and all of its referenced nodes.
		 * Means the subtree held by this node will be printed.
		 *
		 * @param
		 * 		ostram: the ostram to put printed text on
		 */
		virtual void print(std::ostream & os) const;
};

#endif /* DIRECTORY_H_ */
