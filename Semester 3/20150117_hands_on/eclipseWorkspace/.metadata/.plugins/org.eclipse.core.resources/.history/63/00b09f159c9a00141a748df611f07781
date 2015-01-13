/*
 * Node.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: cchet
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
}

Node::Node(const Node& other) :
		firstChild(nullptr), nextSibling(nullptr) {
	if (other.getFirstChild() != nullptr) {
		setFirstChild(other.getFirstChild()->clone());
	}
	if (other.getNextSibling() != nullptr) {
		setNextSibling(other.getNextSibling()->clone());
	}
	Register(NODE_CLASS, OBJECT_CLASS);
}

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
Node* Node::getFirstChild() const {
	return firstChild;
}

Node* Node::getNextSibling() const {
	return nextSibling;
}

void Node::setFirstChild(Node* firstChild) {
	if (this == firstChild) {
		cout << "Node is not allowed to reference itself on firstChild"
				<< flush << endl;
	} else {
		this->firstChild = firstChild;
	} /* if */
}

void Node::setNextSibling(Node* nextSibling) {
	if (this == nextSibling) {
		cout << "Node is not allowed to reference itself on nextSibling"
				<< flush << endl;
	} else {
		this->nextSibling = nextSibling;
	} /* if */
}

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
void Node::print(ostream & os) const {
	os << AsString();
}

Node* Node::clone() const {
	return new Node(*this);
}

////////////////////////////////////////////////////////////
// operator                                               //
////////////////////////////////////////////////////////////
ostream& operator<<(ostream & os, const Node & node) {
	node.print(os);
	return os;
}

//		/**
//		 * Assigns the node to the current Node instance by referencing the same members.
//		 *
//		 * @param
//		 * 		other: the tree to be assigned
//		 */
//		inline Node & operator=(const Node & other) {
//			if (this != &other) {
//				firstChild = other.firstChild;
//				nextSibling = other.nextSibling;
//			}
//			return *this;
//		}
