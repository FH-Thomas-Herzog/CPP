/*
 * FsNode.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: cchet
 */
#include <sstream>
#include "FSNode.h"

using namespace std;
using namespace ML;

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
FsNode::FsNode(const string name) :
		Node(), name(name) {
	Register(FS_NODE_CLASS, NODE_CLASS);
}

FsNode::FsNode(const FsNode & other) :
		Node::Node(other), name("copy_of_" + name) {
	Register(FS_NODE_CLASS, NODE_CLASS);
}

FsNode::~FsNode() {
}

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
string FsNode::getName() const {
	return name;
}

FsNode* FsNode::getFirstChild() const {
	return (FsNode*) Node::getFirstChild();
}

FsNode* FsNode::getNextSibling() const {
	return (FsNode*) Node::getNextSibling();
}

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
string FsNode::AsString() {
	stringstream ss;
	ss << "FsNode('" << name << "')";
	return ss.str();
}

FsNode* FsNode::clone() const {
	return new FsNode(*this);
}
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
