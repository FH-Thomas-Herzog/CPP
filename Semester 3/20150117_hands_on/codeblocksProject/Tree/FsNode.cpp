/*
 * FsNode.cpp
 * This is the implementaion of the Fsnode specification.
 *
 *  Created on: Jan 11, 2015
 *      Author: Thomas Herzog
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
} /* FsNode::FsNode */

FsNode::FsNode(const FsNode & other) :
		Node::Node(other), name("copy_of_" + name) {
	Register(FS_NODE_CLASS, NODE_CLASS);
} /* FsNode::FsNode */

FsNode::~FsNode() {
} /* FsNode::~FsNode */

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
string FsNode::getName() const {
	return name;
} /* FsNode::getName */

FsNode* FsNode::getFirstChild() const {
	return (FsNode*) Node::getFirstChild();
} /* FsNode::getFirstChild */

FsNode* FsNode::getNextSibling() const {
	return (FsNode*) Node::getNextSibling();
} /* FsNode::getNextSibling */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
string FsNode::AsString() {
	stringstream ss;
	ss << "FsNode('" << name << "')";
	return ss.str();
} /* FsNode::AsString */

FsNode* FsNode::clone() const {
	return new FsNode(*this);
} /* FsNode::clone */
