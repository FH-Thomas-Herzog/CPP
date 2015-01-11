/*
 * IntNode.h
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#ifndef INTNODE_H_
#define INTNODE_H_

#include "Node.h"

#define INT_NODE_CLASS "IntNode"

class IntNode: public Node {
	private:
		////////////////////////////////////////////////////////////
		// Private Members                                        //
		////////////////////////////////////////////////////////////
		int value;

	protected:

		////////////////////////////////////////////////////////////
		// Utils                                                  //
		////////////////////////////////////////////////////////////
		virtual IntNode* clone() const;
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
		IntNode(int value);

		/**
		 * Copy constructor which clones the IntNode deeply.
		 * All references are cloned to, so the whole subtree will be copied.
		 *
		 * @param
		 * 		other: the node to be copied deeply
		 */
		IntNode(const IntNode & other);

		virtual ~IntNode();

		////////////////////////////////////////////////////////////
		// Getter and Setter                                      //
		////////////////////////////////////////////////////////////
		virtual int getValue() const;

		virtual void setValue(int value);

		virtual std::string AsString() const;
};

#endif /* INTNODE_H_ */
