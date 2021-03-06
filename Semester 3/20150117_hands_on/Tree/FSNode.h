/*
 * FSNode.h
 * The FsNode specification which is the root class for the file system nodes.
 *
 *  Created on: Dec 27, 2014
 *      Author: Thomas Herzog
 */

#ifndef FSNODE_H_
#define FSNODE_H_

#include "Node.h"

#define FS_NODE_CLASS "FsNode"

/**
 * This class is the root class for the file system nodes.
 */
class FsNode: public Node {
protected:
	const std::string name;

public:
	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	/**
	 * This class is not allowed to be instantiated via an empty constructor
	 */
	FsNode() = delete;

	/**
	 * Constructs an instance with a name
	 */
	FsNode(const std::string name);

	/**
	 * Copy constructor which performs a deep copy
	 */
	FsNode(const FsNode & other);

	/**
	 * Destructor which does nothing.
	 * Deletion is performed via Node constructor
	 */
	virtual ~FsNode();

	////////////////////////////////////////////////////////////
	// Getter and Setter                                      //
	////////////////////////////////////////////////////////////
	/**
	 * Gets teh first child reference
	 *
	 * @return
	 * 		the hold first child reference
	 */
	virtual FsNode* getFirstChild() const;

	/**
	 * Gets the next sibling reference
	 *
	 * @return
	 * 		the held next sibling reference
	 */
	virtual FsNode* getNextSibling() const;

	////////////////////////////////////////////////////////////
	// Utils                                                  //
	////////////////////////////////////////////////////////////
	/**
	 * Returns the string representation of this class
	 *
	 * @return
	 * 		the string representation of this class
	 */
	virtual std::string AsString();

	/**
	 * Performs a deep copy of this class
	 *
	 * @return
	 * 		the copied instance
	 */
	virtual FsNode* clone() const;

	virtual std::string getName() const;
};
#endif /* FSNODE_H_ */
