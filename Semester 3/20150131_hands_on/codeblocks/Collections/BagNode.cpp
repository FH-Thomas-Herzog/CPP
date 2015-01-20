/*
 * BagNode.cpp
 * This is the implementation of the bag container BagNode specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */
#include "BagNode.h"
#include <sstream>

using namespace std;
using namespace ML;

BagNode::BagNode(ML::Object* val, Node* prev, Node* next) :
		Node(val, prev, next), count(1) {
	Register("BagNode", "Node");
} /* BagNode::BagNode */

BagNode::~BagNode() {
	// nothing to do
} /* BagNode::~BagNode */

std::string BagNode::AsString() const {
	string result("BagNode(");
	/* seems std::to_String not supported by this compiler */
	stringstream ss;
	ss << count;
	(val != nullptr) ?
			result.append(val->AsString()) : result.append("nullptr");
	result.append(", ").append(ss.str()).append(")");
	return result;
} /* BagNode::AsString */
