/*
 * FSNode.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FSNODE_H_
#define FSNODE_H_

#include <string>
#include "Node.h"

class FsNode: public Node {
	protected:
		std::string name;

	public:
		/**
		 * Never use default empty constructor because fs node must always have a name.
		 */
		FsNode() = delete;

		inline FsNode(std::string name) :
				Node(), name(name) {
		}

		inline FsNode(const FsNode & other) :
				Node::Node(other), name("copy_of_" + name) {
		}

		virtual inline ~FsNode() {
		}

		virtual inline std::string AsString() {
			std::stringstream ss;
			ss << "FsNode('" << name << "')";
			return ss.str();
		}

		virtual inline FsNode* clone() const {
			return new FsNode(*this);
		}

		virtual inline std::string getName() const {
			return name;
		}
};
#endif /* FSNODE_H_ */
