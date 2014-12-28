/*
 * Node.h
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#ifndef NODE_H_
#define NODE_H_

#include "MLObject.h"
#include "MetaInfo.h"
#include <sstream>

/**
 * This class is the base node which can be used to be handled in a tree.
 * This class provides all necessary methods which a tree node needs.
 */
class Node: public ML::Object {
	protected:
		////////////////////////////////////////////////////////////
		// Private members                                        //
		////////////////////////////////////////////////////////////
		/**
		 * The first direct child reference
		 */
		Node *firstChild;

		/**
		 * The next direct neighbor reference
		 */
		Node *nextSibling;
	public:
		////////////////////////////////////////////////////////////
		// Constructor and Destructor                             //
		////////////////////////////////////////////////////////////
		/**
		 * Default constructor which registers this instance in the mini lib.
		 *
		 * @param
		 * 		firstChild: nullptr for the first child reference
		 * @param
		 * 		nextSibling: nullptr for the first nextSibling reference
		 */
		explicit inline Node(Node *firstChild = nullptr, Node *nextSibling =
				nullptr) :
				firstChild(nullptr), nextSibling(nullptr) {
			Register("Node", "Object");
		}

		/**
		 * Destructor which deletes the held references if they are not null.
		 * Their references nodes will be deleted same as here when their destructor gets called.
		 */
		virtual inline ~Node() {
			if (firstChild != nullptr) {
				delete firstChild;
			} /* if */

			if (nextSibling != nullptr) {
				delete nextSibling;
			} /* if */
		}

		/**
		 * This constructor copies the held nodes which causes that the whole subtree
		 * held by this node is copied.
		 * Therefore that this is a tree node this is no problem,
		 * because recursions are not allowed here.
		 *
		 * @param
		 * 		node: the node to be copied
		 */
		inline Node(const Node& other) :
				firstChild(nullptr), nextSibling(nullptr) {
			if (other.getFirstChild() != nullptr) {
				setFirstChild(other.getFirstChild()->clone());
			}
			if (other.getNextSibling() != nullptr) {
				setNextSibling(other.getNextSibling()->clone());
			}
			/* Only register if instance of Node */
			if (other.Class().compare("Node")) {
				Register("Node", "Object");
			}
		}

		////////////////////////////////////////////////////////////
		// Getter and Setter                                      //
		////////////////////////////////////////////////////////////
		/**
		 * Getter method for the first child references
		 */
		virtual inline Node* getFirstChild() const {
			return firstChild;
		}
		/**
		 * Getter method for the first next neighbor references
		 */
		virtual inline Node* getNextSibling() const {
			return nextSibling;
		}

		/**
		 * Sets the first child references.
		 * The caller is responsible for handling the instance lifecycle of the former referenced node.
		 *
		 * @param
		 * 		firstChild: the new first child node reference
		 */
		virtual inline void setFirstChild(Node* firstChild) {
			if (this == firstChild) {
				std::cout
						<< "Node is not allowed to reference itself on firstChild"
						<< std::flush << std::endl;
			} else {
				this->firstChild = firstChild;
			} /* if */
		}

		/**
		 * Sets the next neighbor references.
		 * The caller is responsible for handling the instance lifecycle of the former referenced node.
		 *
		 * @param
		 * 		nextSibling: the new nextSibling rreference
		 */
		virtual inline void setNextSibling(Node* nextSibling) {
			if (this == nextSibling) {
				std::cout
						<< "Node is not allowed to reference itself on nextSibling"
						<< std::flush << std::endl;
			} else {
				this->nextSibling = nextSibling;
			} /* if */
		}

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
		virtual inline void print(std::ostream & os) const {
			os << AsString();
		}

		virtual inline Node* clone() const {
			return new Node(*this);
		}

		////////////////////////////////////////////////////////////
		// operator                                               //
		////////////////////////////////////////////////////////////
		/**
		 * The friend method for the << operator.
		 *
		 * @param
		 * 		os: the ostream instace to print result on
		 *
		 * @param
		 *  	node: the node part of the operation
		 */
		inline friend std::ostream& operator<<(std::ostream & os,
				const Node & node) {
			node.print(os);
			return os;
		}
};
#endif /* NODE_H_ */
