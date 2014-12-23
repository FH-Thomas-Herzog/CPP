/*
 * Tree.h
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#ifndef TREE_H_
#define TREE_H_

#include <ostream>
#include "Node.h"
#include "MLObject.h"

using namespace std;
using namespace ML;

/**
 * This class represents the tree which is able to handle all derivations of the Node class.
 */
class Tree: public Object {
	private:
		////////////////////////////////////////////////////////////
		// Private Members                                        //
		////////////////////////////////////////////////////////////
		/**
		 * The root node of this tree.
		 * Will be handled by the instance itself and cannot be modified from the caller.
		 */
		Node* root;
		/**
		 * The current size of the tree.
		 * Means the node count.
		 */
		int size;

		////////////////////////////////////////////////////////////
		// Private Utils                                          //
		////////////////////////////////////////////////////////////
		/**
		 * Answers the question if the parent node is handled by this tree instance.
		 *
		 * @param
		 * 		parent: the node to be checked if managed by this tree.
		 */
		bool isManagedNode(const Node* node);

	public:
		////////////////////////////////////////////////////////////
		// Constructor and Destructor                             //
		////////////////////////////////////////////////////////////
		/**
		 * Default constructor which creates a new root node for this tree.
		 */
		inline Tree() :
				root(new Node()), size(0) {
			Register("Tree", "Object");
		}

		/**
		 * The default destructor which deltes its root.
		 * The referenced nodes of the root node will be deleted in the destructor
		 * of the root node same with their descendants.
		 */
		virtual inline ~Tree() {
			if (root != nullptr) {
				delete root;
			}
		}

		////////////////////////////////////////////////////////////
		// Getter and Setter                                      //
		////////////////////////////////////////////////////////////
		/**
		 * Getter method for the root node.
		 *
		 * @return the root node.
		 */
		virtual inline Node* getRoot() const {
			return root;
		}

		/**
		 * The getter for the current size of the tree.
		 */
		virtual inline int getSize() const {
			return size;
		}

		////////////////////////////////////////////////////////////
		// Tree Manipulation                                      //
		////////////////////////////////////////////////////////////
		/**
		 * Inserts a child node for the given parent if the parent is a managed node and the child is not null.
		 *
		 * @param
		 * 		parent: the parent node to append child on
		 * @param
		 * 		child:t he child node to be appended to the given parent node.
		 */
		virtual void insertChild(Node* parent, Node* child);

		/**
		 * Deletes the subtree held by teh given node.
		 *
		 * @param
		 * 		node: the node to be deleted along with its held nodes.
		 */
		virtual void deleteSubTree(Node* node);

		/**
		 * Clears the tree by removing the root references and creating a new root.
		 * Be aware that the caller would be responsible for handling the lifecycle of the formerly managed tree nodes.
		 */
		virtual void clear();

		/**
		 * Deletes all elements including the root.
		 * All nodes will not be available and all held references will become invalid.
		 */
		virtual void deleteElements();

		////////////////////////////////////////////////////////////
		// Utils                                                  //
		////////////////////////////////////////////////////////////
		/**
		 * Prints this tree and all of its held nodes.
		 *
		 * @param
		 * 		os: the ostram isntance ot print the result.
		 */
		virtual void print(ostream & os) const;

		////////////////////////////////////////////////////////////
		// Friends                                                //
		////////////////////////////////////////////////////////////
		/**
		 * The friend method which handles the operator <<.
		 *
		 * @param
		 * 		os: the ostream where to put result on
		 * @param
		 * 		tree: the tree part of this operation
		 */
		inline friend ostream& operator<<(ostream & os, const Tree & tree) {
			tree.print(os);
			return os;
		}
};

#endif /* TREE_H_ */
