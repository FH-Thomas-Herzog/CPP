/*
 * IntNode.cpp
 * This is the implementation of the IntNode specification.
 *
 *  Created on: Jan 11, 2015
 *      Author: Thomas Herzog
 */
#include <ostream>
#include <string>
#include <sstream>
#include "IntNode.h"
#include "MetaInfo.h"

using namespace std;
using namespace ML;

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
IntNode::IntNode(int value) :
		Node(), value(value) {
	Register(INT_NODE_CLASS, NODE_CLASS);
} /* IntNode::IntNode */

IntNode::IntNode(const IntNode & other) :
		Node(other), value(other.getValue()) {
	Register(INT_NODE_CLASS, NODE_CLASS);
} /* IntNode::IntNode */

IntNode::~IntNode() {
} /* IntNode::~IntNode */

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
int IntNode::getValue() const {
	return value;
} /* IntNode::getValue */

void IntNode::setValue(int value) {
	this->value = value;
} /* IntNode::setValue */

string IntNode::AsString() const {
	stringstream ss;
	ss << "IntNode(" << value << ")" << flush;
	return ss.str();
} /* IntNode::AsString */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
IntNode* IntNode::clone() const {
	return new IntNode(*this);
} /* IntNode::clone */
