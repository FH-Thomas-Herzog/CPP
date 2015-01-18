/*
 * BagNode.h
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */

#ifndef BAGNODE_H_
#define BAGNODE_H_

#include "List.h"
#include <string>

/**
 * This class can be used in bag implementation which holds information about the count of the duplicates.
 * Therefore that we talk about duplicates we do not need to hold the references, just the count is needed.
 */
class BagNode: public Node {
	public:
		/**
		 * The count of the nodes.
		 */
		int count;

		/**
		 * Constructor which delegates to the parent class and sets count initially to 1.
		 */
		BagNode(ML::Object* val = nullptr, Node* prev = nullptr, Node* next =
				nullptr);

		/**
		 * Destructor which does nothing because no dynamic members.
		 */
		~BagNode();

		/**
		 * Returns the string representation of this instance.
		 */
		virtual std::string AsString() const;
};

#endif /* BAGNODE_H_ */
