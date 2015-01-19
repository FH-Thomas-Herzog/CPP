/*
 * Node.cpp
 * This is the implementation of the container Node specification.
 *
 *  Created on: Jan 17, 2015
 *      Author: Thomas Herzog
 */

#include "MLCollection.h"
#include "Node.h"
#include <string>

using namespace std;
using namespace ML;

Node::Node(Object* val, Node* prev, Node* next) :
		val(val), prev(prev), next(next) {
	Register("Node", "Object");
} /* Node::Node */

Node::~Node() {
	// Nothing to do. Member handled outside this instance
} /* Node::~Node */

string Node::AsString() const {
	string asString("Node (");
	(val != nullptr) ?
			asString.append(val->AsString()) : asString.append("nullptr");
	asString.append(")");
	return asString;
} /* Node::AsString */

