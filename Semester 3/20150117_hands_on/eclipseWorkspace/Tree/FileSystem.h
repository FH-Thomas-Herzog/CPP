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
		FsErrorType error = FsErrorType::NONE;
		FsNode* lastVisitedNode;
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
		 * If the childName contains a path to it will append the path to the path which is used for the resolving.
		 * If the path is invalid an error code will be set.
		 * The result struct will contain the references to the last visited node.
		 * The result will get the childName set.
		 *
		 * @param
		 * 		path: the path to be validated
		 * @param
		 * 		childName: the name of the child
		 * @return
		 * 		the result struct which contains information about the path and a reference to the last visited node
		 */
		WalkResult validatePath(const std::string & path, const std::string childName) const;

		/**
		 * This method recursively walks the given full path.
		 * If the path is invalid a error code is set for later evaluation.
		 * The reference to last visited node is set.
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
		 * Gets the direct of the given parent which defines the given name
		 *
		 * @param
		 * 		node: the parent node to be searched on
		 * @param
		 * 		name: the name of the searched child
		 * @return
		 * 		the found node, null otherwise
		 */
		FsNode* getChildByName(const FsNode* node,
				const std::string & name) const;

		/**
		 * Deletes the given child from the parent safely.
		 *
		 * @param
		 * 		parent: the parent node to delete child from
		 * @param
		 * 		child:t he child to be deleted from the parent safely
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
		FileSystem();

		FileSystem(const FileSystem & other);

		virtual ~FileSystem();

		////////////////////////////////////////////////////////////
		// public visible methods                                 //
		////////////////////////////////////////////////////////////
		/**
		 * Touches a file and creates one if the file does not exist
		 *
		 * @param
		 * 		path: the path to the file
		 * 	param
		 * 		filename: the name of the file to be touched
		 */
		virtual void touch(const std::string & path,
				const std::string & filename);

		/**
		 * Creates a directory.
		 *
		 * @param
		 * 		path: the path under which the directory shall be created
		 * @param
		 * 		dirname: the name of the directory to be created
		 */
		virtual void mkdir(const std::string & path,
				const std::string & dirname);

		/**
		 * Removes a file from the given path.
		 *
		 * @param
		 * 		path: the path where the file resides
		 * @param
		 * 		filename: the name of the file to be deleted
		 */
		virtual void rm(const std::string & path, const std::string & filename);

		/**
		 * Removes a directory from the given path.
		 *
		 * @param
		 * 		path: the path where the directory resides
		 * @param
		 * 		filename: the name of the file to be deleted
		 */
		virtual void rmdir(const std::string & path,
				const std::string & dirname);

		/**
		 * List all of the content of the file system
		 */
		virtual void ls() const;
};

#endif /* FILESYSTEM_H_ */