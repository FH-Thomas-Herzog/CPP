/*
 * Bag.h
 * This is the Bag container specification.
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */

#ifndef BAG_H_
#define BAG_H_

#include "Set.h"
#include "BagNode.h"

/**
 * This class realizes a bag container and inherits from the Set class which provides the proper implementation.
 * Since this container will not contain duplicates nodes (duplicates count on BagNode only), we can inherit from Set
 * and not from List.
 * There is no need to create own nodes for the duplicates since the duplicates will not provide more information
 * as the unique instance would do.
 */
class Bag: public Set {
	protected:
		/**
		 * Overwritten for type safety.
		 * @see: Node* Set::Find(Object* obj)
		 */
		BagNode* Find(ML::Object* object) const;

	public:
		// #########################################################
		// Constructor and destructor
		// #########################################################
		/**
		 * Constructor which does nothing because handled by parent class
		 */
		Bag();

		/**
		 * Destructor which does nothing because no dynamic members.
		 */
		virtual ~Bag();

		// #########################################################
		// overwritten for Bag behavior
		// #########################################################
		/**
		 * Overwritten to allow duplicates and handle them properly.
		 * @see Set::Add(Object* object)
		 */
		virtual void Add(ML::Object* object);

		/**
		 * Overwritten to allow duplicates and handle them properly.
		 * @see Set::Append(Object* object)
		 */
		virtual void Append(ML::Object* object);

		/**
		 * Overwritten to allow duplicates and handle them properly.
		 * @see Set::Prepend(Object* object)
		 */
		virtual void Prepend(ML::Object* object);

		/**
		 * Deletes one of the duplicates if more than one item is present otherwise parent class handles deletion.
		 *
		 * @param:
		 * 		object: the object to be deleted
		 */
		virtual ML::Object* Remove(ML::Object* object);

		// #########################################################
		// overwritten for type safety and bag behavior .utils
		// #########################################################
		/**
		 * Special handling for Bag container, since a set is not allowed to contain duplicates but a bag does
		 * we need to handle this intersection differently.
		 *
		 * 1. If a target node does not exist in the source will be removed completely.
		 * 2. If a target node has less duplicates defined than the target node will remain as it is.
		 * 3. If a target node has more duplicates defined as the source node than the target node will define the source node defined duplicate count.
		 *
		 */
		virtual void Intersect(Bag* bag);

		/**
		 * Special handling for Bag container, since since a set is not allowed to contain duplicates but a bag does
		 * we need to handle this intersection differently.
		 *
		 * 1. If a node exists in the source but not the target then this node will be appended to this container with the
		 *    current set duplicate count of the source node
		 * 2. If a target node has lees duplicates as a source node increases the duplicate counter to face the source node duplicate count.
		 * 3. If a target node has more duplicates defined as the source node will not be modified.
		 */
		virtual void Union(Bag* bag);

		/**
		 * Special handling for Bag container, since since a set is not allowed to contain duplicates but a bag does
		 * we need to handle this intersection differently.
		 *
		 * 1. If a node exists in the source and target and the target node has more duplicates defined,
		 *    then the target node will define the sum: targetNode.count - sourceNode.count;
		 * 2. If a node exists in the source and target node and the target node has less duplicates defined,
		 *    then the node will be removed completely
		 * 3. If a target node does not exist in the source then this node remains as it is
		 */
		virtual void Complement(Bag* bag);

		// #########################################################
		// operator
		// #########################################################
		/**
		 * The operator which prints this bag instance.
		 * The already in List implemented Method Print will be reused since there is no difference in the printed result.
		 * The nodes will provide their own AsString method and therefore the nodes will be printed properly.
		 */
		friend std::ostream & operator<<(std::ostream & os, const Bag & bag);

};

#endif /* BAG_H_ */
