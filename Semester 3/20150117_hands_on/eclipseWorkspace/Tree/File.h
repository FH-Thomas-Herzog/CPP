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

	public:

		File(const std::string filename);

		File(const File & other);

		virtual ~File();

		virtual std::string AsString();
};

#endif /* FILE_H_ */
