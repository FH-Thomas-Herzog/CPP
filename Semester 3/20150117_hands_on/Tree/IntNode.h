/*
 * IntNode.h
 * The specification for the IntNode.
 *
 *  Created on: Dec 23, 2014
 *      Author: Thomas Herzog
 */

#ifndef INTNODE_H_
#define INTNODE_H_

#include "Node.h"

#define INT_NODE_CLASS "IntNode"

/**
 * This class inherit Node class and defines a int value which can be accessed via its defined getter method.
 *
 */
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
	 * 		value: the value to be hold by this IntNode
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

	/**
	 * The destructor of this class which does nothing because deletion is performed via Node
	 * implemented destructor.
	 */
	virtual ~IntNode();

	////////////////////////////////////////////////////////////
	// Getter and Setter                                      //
	////////////////////////////////////////////////////////////
	/**
	 * Gets the hold value,
	 *
	 * @return
	 * 		the hold value
	 */
	virtual int getValue() const;

	/**
	 * Sets a new value.
	 *
	 * @param
	 * 		value: the value to bet set
	 */
	virtual void setValue(int value);

	/**
	 * Returns a string representation of this class.
	 *
	 * @return
	 * 		the string representation of this class
	 */
	virtual std::string AsString() const;

	////////////////////////////////////////////////////////////
	// Utils                                                  //
	////////////////////////////////////////////////////////////
	/**
	 * This method clones this node by copying the held references of this node.
	 *
	 * @return
	 * 		A deep copy of this node
	 */
	virtual IntNode* clone() const;
};

#endif /* INTNODE_H_ */
