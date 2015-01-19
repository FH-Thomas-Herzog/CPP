/*
 * Node.h
 * This is the specification of the container Node.
 *
 *  Created on: Jan 17, 2015
 *      Author: Thomas Herzog
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "MLObject.h"

/**
 * This class is used to wrap a value into a node instance to be able to manage values with a container implementation.
 */
class Node: public ML::Object {

	public:
		/**
		 * The wrapped value
		 */
		ML::Object* val;
		/**
		 * The pointer to the previous node
		 */
		Node* prev;
		/**
		 * The pointer to the next node
		 */
		Node* next;

		// #########################################################
		// Constructor and destructor
		// #########################################################
		/**
		 * Constructor which realizes null values for not defined formal parameters.
		 *
		 * @param:
		 * 		val: the to wrap value (default nullptr)
		 * @param:
		 * 		prev: the reference to the previous node (default nullptr)
		 * @param:
		 * 		next: the reference to the next node (default nullptr)
		 */
		explicit Node(ML::Object* val = nullptr, Node* prev = nullptr,
				Node* next = nullptr);

		/**
		 * This destructor does nothing because values are managed by this node for container usage only.
		 * The lifecycle of the values is managed by the caller not the node or the container
		 */
		virtual ~Node();

		// #########################################################
		// Utils
		// #########################################################
		/**
		 * Returns a string representation of this node and its value.
		 *
		 * @return:
		 * 		the string representation of this node
		 */
		virtual std::string AsString() const;
};

#endif /* NODE_H_ */
