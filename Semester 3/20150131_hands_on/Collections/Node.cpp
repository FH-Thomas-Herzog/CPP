/*
 * Node.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: cchet
 */
#include "MLCollection.h"
#include "Node.h"
#include <string>

using namespace std;
using namespace ML;

Node::Node(Object* val, Node* prev, Node* next) :
		val(val), prev(prev), next(next) {
	Register("Node", "Object");
}

Node::~Node() {
	// Nothing to do. Member handled outside this instance
}

string Node::AsString() const {
	string asString("Node (");
	(val != nullptr) ?
			asString.append(val->AsString()) : asString.append("nullptr");
	asString.append(")");
	return asString;
}

