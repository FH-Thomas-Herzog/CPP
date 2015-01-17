/*
 * List.h
 *
 *  Created on: Jan 17, 2015
 *      Author: cchet
 */

#ifndef LIST_H_
#define LIST_H_

#include "MLCollection.h"
#include "MLObject.h"
#include "Node.h"

class List: public ML::Collection {
	private:
		Node* start;
		int size;

		bool CheckList() const;

		Node* Find(ML::Object* object) const;

	public:
		List();

		~List();

		int Size() const;

		void Add(ML::Object* object);

		ML::Object* Remove(ML::Object* object);

		bool Contains(ML::Object* object) const;

		void Clear();

		ML::Iterator* NewIterator() const;

		virtual void Prepend(ML::Object* object);

		virtual void Append(ML::Object* object);
};

class ListIterator: public ML::Iterator {

		friend ML::Iterator* List::NewIterator() const;

	private:
		Node* current;
		ListIterator(Node* head);

	public:
		~ListIterator();

		ML::Object *Next();
};

#endif /* LIST_H_ */
