/*
 * Directory.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include <string>
#include "FSNode.h"

class Directory: public FsNode {
	private:

	public:
		virtual inline std::string AsString() {
			std::stringstream ss;
			ss << "Directory('" << name << "')";
			return ss.str();
		}

		inline Directory(const Directory & other) :
				FsNode::FsNode(other) {
		}

		virtual inline ~Directory() {
		}

		virtual inline Directory* clone() const {
			return new Directory(*this);
		}
};

#endif /* DIRECTORY_H_ */
