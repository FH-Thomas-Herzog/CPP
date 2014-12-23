/*
 * Node.h
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#ifndef NODE_H_
#define NODE_H_

#include "MLObject.h"
#include <sstream>

using namespace std;
using namespace ML;

/**
 * This class is the base node which can be used to be handled in a tree.
 * This class provides all necessary methods which a tree node needs.
 */
class Node: public Object {
	private:
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
				cout << "deleting firstChild" << flush << endl;
				delete firstChild;
			} /* if */

			if (nextSibling != nullptr) {
				cout << "deleting nextSibling" << flush << endl;
				delete nextSibling;
			} /* if */
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
		virtual inline Node* getNextSbiling() const {
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
				cout << "Node is not allowed to reference itself on firstChild"
						<< flush << endl;
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
				cout << "Node is not allowed to reference itself on nextSibling"
						<< flush << endl;
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
		virtual inline void print(ostream & os) const {
			os << AsString() << " - ";
			if (nextSibling != nullptr) {
				os << nextSibling->AsString() << " - ";
				if (nextSibling->getNextSbiling()) {
					nextSibling->getNextSbiling()->print(os);
				} /* if */
			} /* if */
			if (firstChild != nullptr) {
				os << firstChild->AsString() << " - ";
				if (firstChild->getFirstChild() != nullptr) {
					firstChild->getFirstChild()->print(os);
				} /* if */
			} /* if */
			os << flush << endl;
		}

		////////////////////////////////////////////////////////////
		// Friends                                                //
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
		inline friend ostream& operator<<(ostream & os, const Node & node) {
			node.print(os);
			return os;
		}
};
#endif /* NODE_H_ */
