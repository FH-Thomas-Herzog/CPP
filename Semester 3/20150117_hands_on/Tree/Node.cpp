/*
 * Node.cpp
 * This is the implementation of the IntNode specification.
 *
 *  Created on: Jan 11, 2015
 *      Author: Thomas Herzog
 */
#include "MLObject.h"
#include "MetaInfo.h"
#include "Node.h"

using namespace std;
using namespace ML;

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
Node::~Node() {
	if (firstChild != nullptr) {
		delete firstChild;
	} /* if */

	if (nextSibling != nullptr) {
		delete nextSibling;
	} /* if */
} /* Node::~Node */

Node::Node(const Node& other) :
		firstChild(nullptr), nextSibling(nullptr) {
	if (other.getFirstChild() != nullptr) {
		setFirstChild(other.getFirstChild()->clone());
	}
	if (other.getNextSibling() != nullptr) {
		setNextSibling(other.getNextSibling()->clone());
	}
	Register(NODE_CLASS, OBJECT_CLASS);
} /* Node::Node */

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
Node* Node::getFirstChild() const {
	return firstChild;
} /* Node::getFirstChild */

Node* Node::getNextSibling() const {
	return nextSibling;
} /* Node::getNextSibling */

void Node::setFirstChild(Node* firstChild) {
	if (this == firstChild) {
		cout << "Node is not allowed to reference itself on firstChild"
				<< flush << endl;
	} else {
		this->firstChild = firstChild;
	} /* if */
} /* Node::setFirstChild */

void Node::setNextSibling(Node* nextSibling) {
	if (this == nextSibling) {
		cout << "Node is not allowed to reference itself on nextSibling"
				<< flush << endl;
	} else {
		this->nextSibling = nextSibling;
	} /* if */
} /* Node::setNextSibling */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
void Node::print(ostream & os) const {
	os << AsString();
} /* Node::print */

Node* Node::clone() const {
	return new Node(*this);
} /* Node::clone */

////////////////////////////////////////////////////////////
// operator                                               //
////////////////////////////////////////////////////////////
ostream& operator<<(ostream & os, const Node & node) {
	node.print(os);
	return os;
} /* operator<< */
