/*
 * List.h
 * This is the implementation of the List container specification.
 *
 *  Created on: Jan 17, 2015
 *      Author: Thomas Herzog
 */

#ifndef LIST_H_
#define LIST_H_

#include <ostream>
#include "MLCollection.h"
#include "MLObject.h"
#include "Node.h"

/**
 * This is a list container which allows to manage nodes in a double connected list with anchor structure.
 * This structure was chosen because we want to avoid special cases.
 * No it is simple to append and prepend values since it is always the same an null values cannot occur.
 */
class List: public ML::Collection {

	protected:
		/**
		 * The anchor holding the list elements
		 */
		Node* anchor;

		/**
		 * The size of this list = node count
		 */
		int size;
		/**
		 * Finds a value in this list.
		 *
		 * @param:
		 * 		object: the value wrapped by a managed node
		 * @return:
		 * 		the found node, nullptr otherwise
		 */
		virtual Node* Find(ML::Object* object) const;

	public:
		// #########################################################
		// Constructor and destructor
		// #########################################################
		/**
		 * This constructor creates an anchor element needed by the double connected list with anchor element.
		 * This anchor is initialized properly.
		 */
		List();

		/**
		 * This destructor clears the list and deletes the anchor element.
		 */
		~List();

		// #########################################################
		// Collection manipulation
		// #########################################################
		/**
		 * Adds a item to the list.
		 * The item is wrapped into a node.
		 * Default behavior is to prepend the item to the list.
		 *
		 * @param:
		 * 		object: the value to be added to the list with a wrapping node instance
		 */
		virtual void Add(ML::Object* object);

		/**
		 * Prepends a value to the start of the list by wrapping it into a node instance.
		 *
		 * @param
		 * 		object: the object to be prepended to the list via a wrapping node instance
		 */
		virtual void Prepend(ML::Object* object);

		/**
		 * Appends a value to the end of the list by wrapping it into a node instance.
		 *
		 * @param
		 * 		object: the object to be appended to the list via  wrapping node instance
		 */
		virtual void Append(ML::Object* object);

		/**
		 * Removes the item from the list.
		 * The wrapped value is not deleted but the wrapping node is.
		 *
		 * @param:
		 * 		object: the item to be removed from the list
		 * @return:
		 * 		the removed object, nullptr if the object is not managed by this list
		 */
		ML::Object* Remove(ML::Object* object);

		/**
		 * Clears the list by removing all nodes from the list.
		 * The node instances will be deleted but not the wrapped values.
		 * The caller is responsible for the lifecycle of the managed values.
		 * The anchor will remain as it is.
		 */
		void Clear();

		// #########################################################
		// Utils
		// #########################################################
		/**
		 * Answers the question if the given value is managed by this list.
		 *
		 * @param:
		 * 		object: the value to be checked if managed by this list.
		 * @return:
		 * 		true if the value is managed by this list, false otherwise
		 */
		bool Contains(ML::Object* object) const;

		/**
		 * Creates a new iterator which allows to iterate over the list
		 * starting from the first node.
		 *
		 * @return:
		 * 		the iterator for this list
		 */
		ML::Iterator* NewIterator() const;

		/**
		 * Prints this list and its managed nodes to the ostream instance.
		 *
		 * @param:
		 * 		ostream: the ostream to append the resulting print on
		 */
		void Print(std::ostream & os) const;

		// #########################################################
		// Getter and setter
		// #########################################################
		/**
		 * Returns the current size of this list = node count
		 *
		 * @return:
		 * 		the current node count
		 */
		int Size() const;

		// #########################################################
		// operator
		// #########################################################
		/**
		 * operator for this implementation which calls the Print Method on the given list.
		 *
		 * @param:
		 * 		ostream: the ostream to append result print on
		 * @param:
		 * 		list: the list to print out
		 * @return:
		 * 		the ostream with appended print result
		 */
		friend std::ostream & operator<<(std::ostream & os, const List & list);
};

/**
 * This is the list iterator which allows to iterate over a list instance.
 */
class ListIterator: public ML::Iterator {

		/**
		 * Crates a new iterator for a list.
		 *
		 * @return:
		 * 		the iterator instance for this list
		 */
		friend ML::Iterator* List::NewIterator() const;

	private:
		/**
		 * The pointer to current visited node.
		 */
		Node* current;
		/**
		 * The anchor node of the list
		 */
		Node* anchorNode;

		// #########################################################
		// Constructor
		// #########################################################
		/**
		 * Private constructor because it is not allowed to instantiate a list iterator
		 * outside the list implementation.
		 *
		 * @param:
		 * 		anchor: the anchor node
		 * @param:
		 * 		start: the start node of the list
		 */
		ListIterator(Node* anchorNode, Node* start);

	public:
		// #########################################################
		// Destructor
		// #########################################################
		/**
		 * Destructor which does nothing because nodes values are managed by the list only.
		 */
		~ListIterator();

		// #########################################################
		// Utils
		// #########################################################
		/**
		 * Returns the next element of the managed list.
		 *
		 * @return:
		 * 		the next node nullptr otherwise
		 */
		ML::Object *Next();
};

#endif /* LIST_H_ */
