/*
 * IntNode.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: cchet
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
}

IntNode::IntNode(const IntNode & other) :
		Node(other), value(other.getValue()) {
	Register(INT_NODE_CLASS, NODE_CLASS);
}

IntNode::~IntNode() {
}

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
int IntNode::getValue() const {
	return value;
}

void IntNode::setValue(int value) {
	this->value = value;
}

string IntNode::AsString() const {
	stringstream ss;
	ss << "IntNode(" << value << ")" << flush;
	return ss.str();
}

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
IntNode* IntNode::clone() const {
	return new IntNode(*this);
}
