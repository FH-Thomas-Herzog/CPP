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
bool Tree::isManagedNode(const Node* node) const {
	bool childResult = false;
	bool siblingResult = false;
	Node* child;
	Node* next;

	if ((node != nullptr) && (!(childResult = (root == node)))) {
		child = root->getFirstChild();
		while ((child != nullptr) && (!siblingResult)
				&& (!(childResult = (child == node)))) {
			siblingResult = false;
			next = child->getNextSbiling();
			while ((next != nullptr) && ((!(siblingResult = (next == node))))) {
				next = next->getNextSbiling();
			}
			child = child->getFirstChild();
		}
	} /* if */

	return childResult || siblingResult;
} /* Tree::isManagedNode */

int Tree::countNodes(const Node* node) const {
	int result = 0;

	if (node != nullptr) {
		result++;
		Node* tmp = node->getNextSbiling();
		while (tmp != nullptr) {
			tmp = tmp->getNextSbiling();
			result++;
		} /* while */
		return result + countNodes(node->getFirstChild());
	} /* if */

	return result;
} /* Tree::countNodes */

Node* Tree::getParentNode(Node* subTreeRoot, const Node* node) const {
	Node* result = nullptr;
	Node* next;

	if ((subTreeRoot != nullptr) && (node != nullptr)) {
		result = (subTreeRoot->getFirstChild() == node) ? subTreeRoot : nullptr;
		next = subTreeRoot->getNextSbiling();
		while ((next != nullptr) && (result == nullptr)) {
			result = getParentNode(next->getFirstChild(), node);
			next = next->getNextSbiling();
		} /* while */
		if (result == nullptr) {
			result = getParentNode(subTreeRoot->getFirstChild(), node);
		}
	} /* if */

	return result;
} /* Tree::getParentNode */

Node* Tree::getFormerNeighbour(Node* parent, const Node* node) const {
	Node* result = nullptr;

	if ((parent != nullptr) && (node != nullptr)) {
		Node* pre = parent;
		Node* cur = parent->getNextSbiling();
		while ((cur != nullptr) && (cur != node)) {
			pre = cur;
			cur = cur->getNextSbiling();
		} /* while */
		result =
				(cur == node) ?
						pre : getFormerNeighbour(parent->getFirstChild(), node);
	} /* if */

	return result;
} /* Tree::getFormerNeighbour */

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
		child->setFirstChild(parent->getFirstChild()->getFirstChild());
		parent->setFirstChild(child);
	} /* if */

	size++;

} /* Tree::insertChild */

void Tree::deleteSubTree(Node* node) {
	bool isRoot = false;
	Node* tmp = nullptr;

	/* Error if instance is not managed */
	if (!isManagedNode(node)) {
		cout << "Cannot delete unmanaged subtree !!! node: " << node->AsString()
				<< endl << flush;
	} else {
		/* check if root node */
		if (root == node) {
			isRoot = true;
		}
		/* handle references to sub tree root */
		else {
			/* cut from first child list if found here */
			if ((tmp = getParentNode(root, node)) != nullptr) {
				tmp->setFirstChild(node->getNextSbiling());
			}
			/* Cut from sibling list if found there */
			else if ((tmp = getFormerNeighbour(root, node)) != nullptr) {
				tmp->setNextSibling(tmp->getNextSbiling()->getNextSbiling());
			}
			/* need to remove reference because otherwise would be deleted along with the node */
			node->setNextSibling(nullptr);
		}/* if */

		/* delete the sub tree */
		delete node;
		node = nullptr;

		/* re initialize if it is root */
		if (isRoot) {
			init();
		} else {
			size = countNodes(root);
		}/* if */
	} /* if */
} /* Tree::deleteSubTree */

void Tree::deleteElements() {
	deleteSubTree(root);
} /* Tree::deleteElements */

void Tree::clear() {
	init();
} /* Tree::clear */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
void Tree::print(ostream & os) const {
	cout << "##################################################" << endl;
	cout << "node count: " << size << endl;
	cout << "##################################################" << endl;
	os << root->AsString() << "(root) - ";

	if (root->getFirstChild() != nullptr) {
		root->getFirstChild()->print(os);
	} /* if */

	if (root->getNextSbiling() != nullptr) {
		root->getNextSbiling()->print(os);
	} /* if */
} /* Tree::print */

