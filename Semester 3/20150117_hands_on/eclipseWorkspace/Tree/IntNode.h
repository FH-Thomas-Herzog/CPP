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
#include <sstream>
#include "Node.h"
#include "MetaInfo.h"

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
		/**
		 * Constructor which takes value as the argument
		 *
		 * @param
		 * 		value: teh value to be hold by this IntNode
		 */
		inline IntNode(int value) :
				Node(), value(value) {
			Register("IntNode", "Node");
		}

		/**
		 * Copy constructor which clones the IntNode deeply.
		 * All references are cloned to, so the whole subtree will be copied.
		 *
		 * @param
		 * 		other: the node to be copied deeply
		 */
		inline IntNode(const IntNode & other) :
				Node(other), value(other.getValue()) {
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

		virtual inline std::string AsString() const {
			std::stringstream ss;
			ss << "IntNode(" << value << ")" << std::flush;
			return ss.str();
		}

		////////////////////////////////////////////////////////////
		// Utils                                                  //
		////////////////////////////////////////////////////////////
		virtual inline IntNode* clone() const {
			return new IntNode(*this);
		}
};

#endif /* INTNODE_H_ */
