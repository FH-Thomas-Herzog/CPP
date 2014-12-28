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
			Register("FsNode", "Object");
		}

		inline FsNode(const FsNode & other) :
				Node::Node(other), name("copy_of_" + name) {
			/* Only register if instance of FsNode */
			if (other.Class().compare("FsNode")) {
				Register("FsNode", "Node");
			}
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

		virtual inline FsNode* getFirstChild() const {
			return (FsNode*) Node::getFirstChild();
		}

		virtual inline FsNode* getNextSibling() const {
			return (FsNode*) Node::getNextSibling();
		}
};
#endif /* FSNODE_H_ */
