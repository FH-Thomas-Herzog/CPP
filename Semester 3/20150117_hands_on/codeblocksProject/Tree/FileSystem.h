/*
 * FileSystem.h
 * This is the FileSystem specification
 *
 *  Created on: Dec 27, 2014
 *      Author: Thomas Herzog
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <vector>
#include <string>
#include "Tree.h"
#include "FSNode.h"
#include "File.h"
#include "Directory.h"
#include "FsErrorHandler.h"

/* define file separator for unix and win systems */
#ifdef _WIN32
#define FILE_SEPARATOR   "\\"
#else
#define FILE_SEPARATOR   "/"
#endif

#define FILESYSTEM_CLASS "FileSystem"

/**
 * This struct is used to hold information about the walked path.
 */
typedef struct WalkResult {
	/**
	 * The error type. default NONE.
	 * Indicates an error/successful path walk
	 */
	FsErrorType error = FsErrorType::NONE;
	/**
	 * The last visited node during walking path.
	 * Do not delete this reference is managed by the FileSystem
	 */
	FsNode* lastVisitedNode;
	/**
	 * The actual filename.
	 * Filename is allowed to contain path information and
	 * therefore needs to be extracted and set on the result.
	 * Needs to be deleted by the caller.
	 */
	std::string childNodeName;
} WalkResult;

/**
 * This class represents a Tree implementation which realizes a file system.
 * Therefore that some formerly public visible methods are not allowed to be called
 * by an outside caller, they have been moved to the private section to avoid file system manipulation
 * by the caller outside the newly introduced methods such as mkdir and so on.
 *
 * Therefore that Tree implementation only depends on Node types but this implementations differs between
 * Directory (FsNode) and File(FsNode) where FsNode inherits from Node some methods where overwritten
 * to restrict the the types which must be given by the caller.
 * For instance it is not possible to add a child to a File node, which leads to the fact
 * that only directories are valid parents for inserted Nodes.
 */
class FileSystem: public Tree {
private:
	////////////////////////////////////////////////////////////
	// private utils                                          //
	////////////////////////////////////////////////////////////
	/**
	 * This method validates if the given path is a valid one and only contains directories.
	 * If the childName contains path information the filename will be extracted and set ont he result
	 * and the path information is added to the given path.
	 * If the path is invalid an error code will be set.
	 *
	 * @param
	 * 		path: the path to be validated
	 * @param
	 * 		childName: the name of the child (is allowed to contain path information)
	 * @return
	 * 		the result struct which contains all necessary information about the path and intended child
	 */
	WalkResult validatePath(const std::string & path,
			const std::string childName) const;

	/**
	 * This method recursively walks the given full path defined by the vector.
	 * If the path is invalid a error code is set for later evaluation.
	 * The last visited node is always set. In the case of an error the lastVisited node
	 * will be the node visited before the error occurred, otherwise the last visited node will
	 * point to the last node defined by the full path
	 *
	 * @param
	 * 		currentNode: the node to search for the direct child with the path part set as name
	 * @param
	 * 		fullPath: a vector containing the full path split by the file separator
	 * @param
	 * 		result: the result where the error code and last node are set.
	 */
	void walkPath(const FsNode* currentNode,
			std::vector<std::string> & fullPath, WalkResult & result) const;

	/**
	 * Gets the direct child of the given parent with the given name set.
	 *
	 * @param
	 * 		node: the parent node to search on
	 * @param
	 * 		name: the name of the searched child
	 * @return
	 * 		the found node, null otherwise
	 */
	FsNode* getChildByName(const FsNode* node, const std::string & name) const;

	/**
	 * Deletes the given child from the parent safely.
	 * Means the child is removed from the backed tree nicely.
	 *
	 * @param
	 * 		parent: the parent node to delete child from
	 * @param
	 * 		child: the child to be deleted from the parent safely
	 *
	 */
	void deleteFsNode(FsNode* parent, FsNode* child);

	////////////////////////////////////////////////////////////
	// hidden former public methods                           //
	// for type safety (Node* -> Directory*)                  //
	// not allowed to be called by outside caller             //
	//                                                        //
	// see parent class for method doc                        //
	////////////////////////////////////////////////////////////
	void deleteSubTree(FsNode* node);

	void setRoot(Directory* node);

	void insertChild(Directory* parent, FsNode* child);

	Directory* getRoot() const;

public:
	////////////////////////////////////////////////////////////
	// Constructor and Destructor                             //
	////////////////////////////////////////////////////////////
	/**
	 * Empty constructor which inits the file system with a root directory ""
	 */
	FileSystem();

	/**
	 * Copy constructor which delegates to the parent copy constructor because
	 * no need to perform custom copy
	 */
	FileSystem(const FileSystem & other);

	/**
	 * Destructor which does nothing because cleanup is performed by the base class
	 */
	virtual ~FileSystem();

	////////////////////////////////////////////////////////////
	// public visible methods                                 //
	////////////////////////////////////////////////////////////
	/**
	 * Touches a file and creates one if the file does not exist yet.
	 *
	 * @param
	 * 		path: the path to the file
	 * 	param
	 * 		filename: the name of the file to be touched (allowed to contain path information)
	 */
	virtual void touch(const std::string & path, const std::string & filename);

	/**
	 * Creates a directory if it does not exist yet.
	 *
	 * @param
	 * 		path: the path under which the directory shall be created
	 * @param
	 * 		dirname: the name of the directory to be created (allowed to contain path information)
	 */
	virtual void mkdir(const std::string & path, const std::string & dirname);

	/**
	 * Removes a file from the given path if the file exits.
	 *
	 * @param
	 * 		path: the path where the file resides
	 * @param
	 * 		filename: the name of the file to be deleted
	 */
	virtual void rm(const std::string & path, const std::string & filename);

	/**
	 * Removes a directory from the given path if the directory exists.
	 *
	 * @param
	 * 		path: the path where the directory resides
	 * @param
	 * 		filename: the name of the file to be deleted
	 */
	virtual void rmdir(const std::string & path, const std::string & dirname);

	/**
	 * List all of the content of the file system.
	 * Uses Tree print method of Tree class.
	 */
	virtual void ls() const;
};

#endif /* FILESYSTEM_H_ */
