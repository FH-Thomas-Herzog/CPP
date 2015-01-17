/*
 * Node.h
 *
 *  Created on: Jan 17, 2015
 *      Author: cchet
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "MLObject.h"

class Node: public ML::Object {

	public:
		ML::Object* val;
		Node* prev;
		Node* next;

		/* no argument and 1-3 argument constructor are usable now*/
		explicit Node(ML::Object* val = nullptr, Node* prev = nullptr, Node* next =
				nullptr);

		virtual ~Node();

		virtual std::string AsString() const;
};

#endif /* NODE_H_ */
