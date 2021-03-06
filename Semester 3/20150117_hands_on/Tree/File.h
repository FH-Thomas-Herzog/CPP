/*
 * File.h
 * This is the specification of the File
 *
 *  Created on: Dec 27, 2014
 *      Author: Thomas Herzog
 */

#ifndef FILE_H_
#define FILE_H_

#include "FSNode.h"

#define FILE_CLASS "File"

/**
 * This class represents a file in the file system.
 */
class File: public FsNode {
public:

	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	/**
	 * This class is not allowed to be instantiated via an empty constructor
	 */
	File() = delete;

	/**
	 * Constructs an instance with a name
	 */
	File(const std::string filename);

	/**
	 * Copy constructor which performs a deep copy
	 */
	File(const File & other);

	/**
	 * Destructor which does nothing.
	 * Deletion is performed via Node constructor
	 */
	virtual ~File();

	////////////////////////////////////////////////////////////
	// Getter and Setter                                      //
	////////////////////////////////////////////////////////////
	/**
	 * Getter method for the first child references which will
	 * always return null, because File cannot define a first child.
	 *
	 * @return
	 * 		the first child reference
	 */
	virtual FsNode* getFirstChild() const;

	/**
	 * Does nothin gbecuase file is not allowed to define a first child.
	 *
	 * @param
	 * 		firstChild: the new first child node reference
	 */
	virtual void setFirstChild(FsNode* firstChild);

	////////////////////////////////////////////////////////////
	// Utils                                                  //
	////////////////////////////////////////////////////////////
	/**
	 * Performs a deep copy of this instance.
	 *
	 * @return
	 * 		the copied instance
	 */
	virtual File* clone() const;

	/**
	 * Prints the directory and all of its referenced nodes.
	 * Means the subtree held by this node will be printed.
	 *
	 * @param
	 * 		ostram: the ostram to put printed text on
	 */
	virtual void print(std::ostream & os) const;

	/**
	 * Returns the string representation of this class
	 *
	 * @return
	 * 		the string representation of this class
	 */
	virtual std::string AsString() const;
};

#endif /* FILE_H_ */
