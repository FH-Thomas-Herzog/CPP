/*
 * File.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FILE_H_
#define FILE_H_

#include "FSNode.h"

#define FILE_CLASS "File"

class File: public FsNode {
	protected:

		Node* getFirstChild();

		void setFirstChild(Node* node);

		virtual File* clone() const;

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

	public:

		File(const std::string filename);

		File(const File & other);

		virtual ~File();

		virtual std::string AsString() const;
};

#endif /* FILE_H_ */
