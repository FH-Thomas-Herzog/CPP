/*
 * IntNode.h
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#ifndef INTNODE_H_
#define INTNODE_H_

#include <ostream>
#include <string>
#include "Node.h"

using namespace std;
using namespace ML;

class IntNode: public Node {
	private:
		////////////////////////////////////////////////////////////
		// Private Members                                        //
		////////////////////////////////////////////////////////////
		int value;

	public:
		////////////////////////////////////////////////////////////
		// Constructor and Destructor                             //
		////////////////////////////////////////////////////////////
		inline IntNode(int value) :
				value(value), Node(nullptr, nullptr) {
			Register("IntNode", "Node");
		}

		virtual inline ~IntNode() {
		}

		////////////////////////////////////////////////////////////
		// Getter and Setter                                      //
		////////////////////////////////////////////////////////////
		virtual inline int getValue() const {
			return value;
		}

		virtual inline void setValue(int value) {
			this->value = value;
		}
};

#endif /* INTNODE_H_ */
