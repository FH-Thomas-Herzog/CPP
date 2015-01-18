/*
 * Bag.h
 *
 *  Created on: Jan 18, 2015
 *      Author: cchet
 */

#ifndef BAG_H_
#define BAG_H_

#include "Set.h"
#include "BagNode.h"

class Bag: public Set {
	protected:
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
		 * @see Set::Intersect(Set* set)
		 */
		virtual void Intersect(Bag* bag);

		/**
		 * @see Set::Intersect(Set* set)
		 */
		virtual void Union(Bag* bag);

		/**
		 * @see Set::Intersect(Set* set)
		 */
		virtual void Complement(Bag* bag);

		// #########################################################
		// operator
		// #########################################################
		friend std::ostream & operator<<(std::ostream & os, const Bag & bag);

		/**
		 * @see List::createWrapperInstance(Object* object, Node* prev, Node* next)
		 */
		virtual BagNode* createWrapperInstance(ML::Object* object,
				BagNode* prev, BagNode* next) const;
};

#endif /* BAG_H_ */
