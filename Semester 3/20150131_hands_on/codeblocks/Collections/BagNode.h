/*
 * BagNode.h
 * This is the bag container BagNode specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */

#ifndef BAGNODE_H_
#define BAGNODE_H_

#include "List.h"
#include <string>

/**
 * This class can be used in bag implementation which holds information about the count of the duplicates.
 * Therefore that we talk about duplicates we do not need to hold the references or copy the duplicates, the duplicate count provides enough information,
 * since a bagNode instance will provide all necessary information about the node and its duplicates.
 */
class BagNode: public Node {
	public:
		/**
		 * The count of the duplicate nodes.
		 */
		int count;

		/**
		 * Constructor which only sets the count to 1.
		 * The rest is done by the parent class
		 */
		explicit BagNode(ML::Object* val = nullptr, Node* prev = nullptr, Node* next =
				nullptr);

		/**
		 * Destructor which does nothing because no dynamic members.
		 */
		~BagNode();

		/**
		 * Returns the string representation of this instance.
		 *
		 * @return:
		 * 		the string representation of this node
		 */
		virtual std::string AsString() const;
};

#endif /* BAGNODE_H_ */
