/*
 * File.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FILE_H_
#define FILE_H_

#include <string>
#include <sstream>
#include "FSNode.h"

class File: public FsNode {
	private:

	public:

		inline File(std::string filename) :
				FsNode::FsNode(name) {
		}

		inline File(const File & other) :
				FsNode::FsNode(other) {
		}

		virtual inline ~File() {
		}

		inline Node* getFirstChild() {
			return nullptr;
		}

		inline void setFirstChild(Node* node) {
			// Do nothing here
			std::cout << "File does not allow setting of a first child"
					<< std::endl;
		}

		virtual inline std::string AsString() {
			std::stringstream ss;
			ss << "File('" << name << "')";
			return ss.str();
		}

		virtual inline File* clone() const {
			return new File(*this);
		}
};

#endif /* FILE_H_ */
