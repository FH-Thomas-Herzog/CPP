/*
 * Tree.h
 * The specification of the Tree implementation.
 *
 *  Created on: Dec 23, 2014
 *      Author: Thomas Herzog
 */

#ifndef TREE_H_
#define TREE_H_

#include <ostream>
#include "Node.h"
#include "MLObject.h"

#define TREE_CLASS "Tree"

/**
 * This class represents the tree which is able to handle all derivations of the Node class.
 */
class Tree: public ML::Object {

private:
	Node* root = nullptr;

	int size;
	////////////////////////////////////////////////////////////
	// Private utils method                                   //
	////////////////////////////////////////////////////////////
	/**
	 * Answers the question if the parent node is handled by this tree instance.
	 * This is done by comparing the pointer addresses.
	 *
	 * @param
	 * 		parent: The node to start the search from.
	 * @param
	 * 		searchNode: the node to be searched
	 * @return
	 * 		true if the node is managed, false otherwise
	 */
	bool isManagedNode(const Node* node, const Node* searchNode) const;

	/**
	 * Counts the nodes of this subtree including the given parent node.
	 *
	 * @param
	 * 		node: the node to count hold nodes
	 * @return
	 * 		the count of nodes in the subtree including the root.
	 */
	int countNodes(const Node* node) const;

	/**
	 * Gets the parent node of the given node.
	 * The given subTreeRoot represents the tree or subtree to search for the node and its parent
	 *
	 * @param
	 * 		subTreeRoot: the subtree to search the neighbor of the given node
	 * @param
	 * 		node: the node to search parent for
	 */
	Node* getParentNode(Node* subTreeRoot, const Node* node) const;

	/**
	 * Gets the former neighbor if the parent has the node referenced by its next sibling field.
	 *
	 * @param
	 * 		parent: the subtree to search the neighbor of the given node
	 * @param
	 * 		node: the node to search former neighbor for
	 */
	Node* getFormerNeighbour(Node* parent, const Node* node) const;

public:
	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	/**
	 * Default constructor which creates a new root node for this tree.
	 */
	Tree();

	/**
	 * Copy constructor for this class
	 */
	Tree(Node & root);

	/**
	 * Creates a tree with the given node as root.
	 * If the root node is null then a root must be set via setRoot otherwise no children can be inserted.
	 */
	Tree(Node* root);

	/**
	 * Copies the whole tree held by the root node by copying the root node.
	 * The held nodes copy their held referenced nodes and so the whole tree is copied.
	 *
	 * @param
	 * 		other: the tree to be copied.
	 */
	Tree(const Tree & other);

	/**
	 * The deconstructor of this class.
	 * The nodes are deleted via cascade which starts at the root node.
	 */
	virtual ~Tree();

	////////////////////////////////////////////////////////////
	// Getter and Setter                                      //
	////////////////////////////////////////////////////////////
	/**
	 * Getter method for the root node.
	 *
	 * @return the root node.
	 */
	virtual Node* getRoot() const;

	/**
	 * Setter for root node.
	 *
	 * @param
	 * 		node: the node acting as the root node.
	 */
	virtual void setRoot(Node* node);

	/**
	 * The getter for the current size of the tree.
	 */
	virtual int getSize() const;

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
	virtual void print(std::ostream & os) const;

	////////////////////////////////////////////////////////////
	// Operators                                              //
	////////////////////////////////////////////////////////////
	/**
	 * The friend method which handles the operator <<.
	 *
	 * @param
	 * 		os: the ostream where to put result on
	 * @param
	 * 		tree: the tree part of this operation
	 */
	friend std::ostream& operator<<(std::ostream & os, const Tree & tree);

	/**
	 * Assigns the tree to the current Tree instance by performing a deep copy.
	 *
	 * @param
	 * 		other: the tree to be assigned
	 */
	Tree & operator=(const Tree & other);
};

#endif /* TREE_H_ */
