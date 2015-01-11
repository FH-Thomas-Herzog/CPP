/*
 * FSNode.h
 *
 *  Created on: Dec 27, 2014
 *      Author: cchet
 */

#ifndef FSNODE_H_
#define FSNODE_H_

#include "Node.h"

#define FS_NODE_CLASS "FsNode"

class FsNode: public Node {
	protected:
		const std::string name;

	public:

		FsNode() = delete;

		FsNode(const std::string name);

		FsNode(const FsNode & other);

		virtual ~FsNode();

		virtual std::string AsString();

		virtual FsNode* clone() const;

		virtual std::string getName() const;

		virtual FsNode* getFirstChild() const;

		virtual FsNode* getNextSibling() const;

//		////////////////////////////////////////////////////////////
//		// operator                                               //
//		////////////////////////////////////////////////////////////
//		/**
//		 * Assigns the node to the current Node instance by referencing the same members.
//		 *
//		 * @param
//		 * 		other: the tree to be assigned
//		 */
//		 FsNode & operator=(const FsNode & other) {
//			if (this != &other) {
//				Node::operator =(other);
//				name = other.name;
//			}
//			return *this;
//		}
};
#endif /* FSNODE_H_ */
