/*
 * Set.h
 * This is the specification of the Set container
 *
 *  Created on: Jan 18, 2015
 *      Author: Thomas Herzog
 */

#ifndef SET_H_
#define SET_H_

#include "List.h"

/**
 * This class implements a set container which disallows duplicate values in the container.
 * It inherits from List and adds check functionality on appending methods to check if the value is already managed.
 *
 * There is no need to define new iterator because would not differ from List implemented one.
 */
class Set: public List {
	protected:
		/**
		 * Answers the question if this container has already a node which wraps the given value.
		 * It prints a message to the console if value is already managed by this set.
		 *
		 * @param:
		 * 		obj: the value to be checked if already managed by the set
		 * @return:
		 * 		true if already managed, false otherwise.
		 */
		virtual bool IsAlreadyManaged(ML::Object* obj) const;

	public:
		// #########################################################
		// Constructor and destructor
		// #########################################################
		/**
		 * This constructor does nothing since List provides all necessary functionality.
		 */
		Set();

		/**
		 * This destructor does nothing since this set has no dynamic members.
		 */
		virtual ~Set();

		// #########################################################
		// overwritten for Set behavior
		// #########################################################
		/**
		 * Overwritten to avoid duplicates.
		 * @see List::Add(Object* object)
		 */
		virtual void Add(ML::Object* object);

		/**
		 * Overwritten to avoid duplicates.
		 * @see List::Append(Object* object)
		 */
		virtual void Append(ML::Object* object);

		/**
		 * Overwritten to avoid duplicates.
		 * @see List::Prepend(Object* object)
		 */
		virtual void Prepend(ML::Object* object);

		// #########################################################
		// utils
		// #########################################################
		/**
		 * Builds a intersection between this set and the given one.
		 * This set will be modified and will become the intersected set
		 *
		 * @param:
		 * 		set: the set to intersect with
		 */
		virtual void Intersect(Set* set);

		/**
		 * Builds a union between this set and the given one.
		 * This set will represent the united set.
		 *
		 * @param:
		 * 		set: the set to unite with this set
		 */
		virtual void Union(Set* set);

		/**
		 * Builds a complement between this set and the given one.
		 * This set will represent the complemented set.
		 *
		 * @param:
		 * 		set: the set to build the complemented with this set
		 */
		virtual void Complement(Set* set);
};

#endif /* SET_H_ */
