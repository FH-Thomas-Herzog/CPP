/*
 * Directory.h
 * This is the specification of the Directory
 *
 *  Created on: Dec 27, 2014
 *      Author: Thomas Herzog
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "FSNode.h"

#define DIRECTORY_CLASS "Directory"

/**
 * This class represents a directory in the file system.
 */
class Directory: public FsNode {
public:
	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	/**
	 * This class is not allowed to be instantiated with an empty contructor
	 */
	Directory() = delete;

	/**
	 * Constructs a instance with the given name
	 */
	Directory(const std::string & name);

	/**
	 * Copies the given instance via an deep copy
	 */
	Directory(const Directory & other);

	/**
	 * This destructor does nothing because deletion is performed in Node class
	 */
	virtual ~Directory();

	////////////////////////////////////////////////////////////
	// Utils                                                  //
	////////////////////////////////////////////////////////////
	/**
	 * Performs a deep copy of this instance
	 *
	 * @return
	 * 		the copied instance
	 */
	virtual Directory* clone() const;

	/**
	 * Returns a string representation of this class
	 *
	 * @return
	 * 		the string representation of this class
	 */
	virtual std::string AsString() const;

	/**
	 * Prints the directory and all of its referenced children.
	 * Means the subtree held by this node will be printed.
	 *
	 * @param
	 * 		ostram: the ostram to put printed text on
	 */
	virtual void print(std::ostream & os) const;
};

#endif /* DIRECTORY_H_ */
