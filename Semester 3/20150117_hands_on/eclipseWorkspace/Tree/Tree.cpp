/*
 * Tree.cpp
 *
 *  Created on: Dec 23, 2014
 *      Author: cchet
 */

#include <string>
#include <iostream>
#include "Tree.h"
#include "Node.h"

using namespace std;

////////////////////////////////////////////////////////////
// Private Utils                                          //
////////////////////////////////////////////////////////////
bool Tree::isManagedNode(const Node* node) {
	if (node != nullptr) {
		/* check for root node */
		if (root == node) {
			return true;
		} /* if */

		Node* child = root->getFirstChild();
		/* search on children */
		while (child != nullptr) {
			if (child == node) {
				return true;
			} /* if */

			Node* sibling = child->getNextSbiling();
			/* search on siblings */
			while (sibling != nullptr) {
				if (sibling == node) {
					return true;
				} /* if */

				sibling = child->getNextSbiling();
			} /* while */

			child = child->getFirstChild();
		} /* while */
	} /* if */

	return false;
}

////////////////////////////////////////////////////////////
// Tree Manipulation                                      //
////////////////////////////////////////////////////////////
void Tree::insertChild(Node* parent, Node* child) {
	/* Check for nullptr nodes */
	if ((parent == nullptr) || (child == nullptr)) {
		cout << "Parent and child not are not allowed to be null" << endl
				<< flush;
		return;
	} /* if */

	/* Check for recursions */
	if (parent == child) {
		cout << "Parent and child are not allowed to point to the same node !!!"
				<< endl;
		cout << "parent: " << parent->AsString() << endl;
		cout << "child: " << child->AsString() << endl;
		cout << endl << flush;
		return;
	} /* if */

	/* Check if parent node is managed by this tree */
	if (!isManagedNode(parent)) {
		cout << "Parent is not managed by this tree" << endl << flush;
		return;
	} /* if */

	/* set as first child if no first child present */
	if (parent->getFirstChild() == nullptr) {
		parent->setFirstChild(child);
	}
	/* insert as new first child and move current first child to next sibling of new first child */
	else {
		child->setNextSibling(parent->getFirstChild());
		parent->setFirstChild(child);
	} /* if */

	size++;

} /* Tree::insertChild */

void Tree::deleteSubTree(Node* node) {
	if (node == nullptr) {
		cout << "Cannot delete nullptr" << endl << flush;
	} else {
		delete node;
	} /* if */
}

void Tree::deleteElements() {
	deleteSubTree(root);
	clear();
}

void Tree::clear() {
	root = new Node();
}

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
void Tree::print(ostream & os) const {
	cout << "##################################################" << endl;
	cout << "node count: " << size << endl;
	cout << "##################################################" << endl;
	if (root->getFirstChild() != nullptr) {
		root->getFirstChild()->print(os);
	} /* if */

	if (root->getNextSbiling() != nullptr) {
		root->getNextSbiling()->print(os);
	} /* if */
}

