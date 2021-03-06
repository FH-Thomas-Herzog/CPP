/*
 * Node.h
 * This is the specification of the IntNode
 *
 *  Created on: Dec 23, 2014
 *      Author: Thomas Herzog
 */

#ifndef NODE_H_
#define NODE_H_

#include "MLObject.h"
#include "MetaInfo.h"

#define NODE_CLASS "Node"
#define OBJECT_CLASS "Object"

/**
 * This class is the base node which can be used to be handled in a tree.
 * This class provides all necessary methods which a tree node needs.
 */
class Node: public ML::Object {
	protected:
		Node *firstChild;

		Node *nextSibling;

	public:
		////////////////////////////////////////////////////////////
		// Constructor and Destructor                             //
		////////////////////////////////////////////////////////////
		/**
		 * Default constructor which sets the first child and next sibling to null.
		 *
		 * @param
		 * 		firstChild: nullptr for the first child reference
		 * @param
		 * 		nextSibling: nullptr for the first nextSibling reference
		 */
		explicit inline Node(Node *firstChild = nullptr, Node *nextSibling =
				nullptr) :
				firstChild(nullptr), nextSibling(nullptr) {
			Register(NODE_CLASS, OBJECT_CLASS);
		}

		/**
		 * Destructor which deletes the held references if they are not null.
		 * Their references nodes will be deleted same as here when their destructor gets called.
		 */
		virtual ~Node();

		/**
		 * This constructor copies the held nodes which causes that the whole subtree
		 * held by this node is copied.
		 * Therefore that this is a tree node this is no problem,
		 * because recursions are not allowed here.
		 *
		 * @param
		 * 		node: the node to be copied
		 */
		Node(const Node& other);

		////////////////////////////////////////////////////////////
		// Getter and Setter                                      //
		////////////////////////////////////////////////////////////
		/**
		 * Getter method for the first child references.
		 *
		 * @return
		 * 		the first child reference
		 */
		virtual Node* getFirstChild() const;

		/**
		 * Getter method for the first next neighbor references.
		 *
		 * @return
		 * 		the next sibling reference
		 */
		virtual Node* getNextSibling() const;

		/**
		 * Sets the first child references.
		 * The caller is responsible for handling the instance lifecycle of the former referenced node.
		 *
		 * @param
		 * 		firstChild: the new first child node reference
		 */
		virtual void setFirstChild(Node* firstChild);

		/**
		 * Sets the next neighbor references.
		 * The caller is responsible for handling the instance lifecycle of the former referenced node.
		 *
		 * @param
		 * 		nextSibling: the new nextSibling reference
		 */
		virtual void setNextSibling(Node* nextSibling);

		////////////////////////////////////////////////////////////
		// Utils                                                  //
		////////////////////////////////////////////////////////////
		/**
		 * Prints the node and all of its referenced nodes.
		 * Means the subtree held by this node will be printed.
		 *
		 * @param
		 * 		ostram: the ostram to put printed text on
		 */
		virtual void print(std::ostream & os) const;

		/**
		 * This method clones this node by copying the held references of this node.
		 *
		 * @return
		 * 		A deep copy of this node
		 */
		virtual Node* clone() const;

		////////////////////////////////////////////////////////////
		// operator                                               //
		////////////////////////////////////////////////////////////
		/**
		 * The friend method for the << operator.
		 *
		 * @param
		 * 		os: the ostream instance to print result on
		 *
		 * @param
		 *  	node: the node part of the operation
		 */
		friend std::ostream& operator<<(std::ostream & os, const Node & node);
};
#endif /* NODE_H_ */
