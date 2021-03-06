/*
 * Tree.cpp
 * The implementation of the Tree specification.
 *  Created on: Dec 23, 2014
 *      Author: Thomas Herzog
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Tree.h"
#include "Node.h"

using namespace std;
using namespace ML;

////////////////////////////////////////////////////////////
// Private Utils                                          //
////////////////////////////////////////////////////////////
static void buildLeveledMap(Node* node, int level,
		map<int, vector<Node*>> & resultMap) {

	/* Only if the node is null or has first child */
	if ((node != nullptr) && (node->getFirstChild())) {
		vector<Node*> parents;
		Node* next = node->getFirstChild();
		/* get all nodes with first child set */
		while (next != nullptr) {
			if (next->getFirstChild() != nullptr) {
				parents.push_back(next);
			} /* if */
			next = next->getNextSibling();
		} /* while */

		/* crawl deeper into tree if nodes were found */
		if (parents.size() > 0) {
			resultMap.insert(pair<int, vector<Node*>>(level, parents));
			level++;
			for (unsigned int i = 0; i < parents.size(); i++) {
				buildLeveledMap(parents[i], level, resultMap);
			} /* for */
		} /* if */
	} /* if */
} /* Tree::buildLeveledMap */

bool Tree::isManagedNode(const Node* node, const Node* searchNode) const {
	bool isManaged = false;
	/* recursion anchor */
	if (node != nullptr) {
		isManaged = (node == searchNode);
		if (!isManaged) {
			Node* tmp = node->getFirstChild();
			while ((tmp != nullptr) && (!isManaged)) {
				isManaged = (tmp == searchNode);
				if (tmp->getFirstChild() != nullptr) {
					isManaged = isManagedNode(tmp, searchNode);
				} /* if */
				tmp = tmp->getNextSibling();
			} /* while */
		} /* if */
	} /* if */

	return isManaged;
} /* Tree::isManagedNode */

int Tree::countNodes(const Node* node) const {
	int result = 0;

	if (node != nullptr) {
		result++;
		Node* tmp = node->getNextSibling();
		while (tmp != nullptr) {
			tmp = tmp->getNextSibling();
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
		next = subTreeRoot->getNextSibling();
		while ((next != nullptr) && (result == nullptr)) {
			result = getParentNode(next->getFirstChild(), node);
			next = next->getNextSibling();
		} /* while */
		if (result == nullptr) {
			result = getParentNode(subTreeRoot->getFirstChild(), node);
		} /* if */
	} /* if */

	return result;
} /* Tree::getParentNode */

Node* Tree::getFormerNeighbour(Node* parent, const Node* node) const {
	Node* result = nullptr;

	if ((parent != nullptr) && (node != nullptr)) {
		Node* pre = parent;
		Node* cur = parent->getNextSibling();
		while ((cur != nullptr) && (cur != node)) {
			pre = cur;
			cur = cur->getNextSibling();
		} /* while */
		result =
				(cur == node) ?
						pre : getFormerNeighbour(parent->getFirstChild(), node);
	} /* if */

	return result;
} /* Tree::getFormerNeighbour */

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
Tree::Tree() :
		Tree(nullptr) {
} /* Tree::Tree */

Tree::Tree(Node & root) :
		Tree(&root) {
} /* Tree::Tree */

Tree::Tree(Node* root) :
		root(root) {
	if (root != nullptr) {
		size = countNodes(root);
	}
	Register(TREE_CLASS, OBJECT_CLASS);
} /* Tree::Tree */

Tree::Tree(const Tree & other) :
		size(other.getSize()) {
	if (other.getRoot() != nullptr) {
		root = other.getRoot()->clone();
	} /* if */
	Register(TREE_CLASS, OBJECT_CLASS);
} /* Tree::Tree */

Tree::~Tree() {
	if (root != nullptr) {
		delete root;
	} /* if */
} /* Tree::~Tree */

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
Node* Tree::getRoot() const {
	return root;
} /* Tree::getRoot */

void Tree::setRoot(Node* node) {
	/* check for valid new root node */
	if ((node == nullptr) || (node->getNextSibling() != nullptr)) {
		cout
				<< "root node must not be null and must not have next sibling set !!!"
				<< endl;
	}
	/* if current root node is not null delete it */
	else if (root != nullptr) {
		deleteElements();
		/* clear tree */
		clear();
	} /* if */

} /* Tree::setRoot */

int Tree::getSize() const {
	return size;
} /* Tree::getSize */

////////////////////////////////////////////////////////////
// Tree Manipulation                                      //
////////////////////////////////////////////////////////////
void Tree::insertChild(Node* parent, Node* child) {
	/* Check if root is defined */
	if (root == nullptr) {
		cout
				<< "Cannot add child on empty tree !!! At least the root node must be defined !!!"
				<< endl << flush;
	}
	/* Check for nullptr nodes */
	else if ((parent == nullptr) || (child == nullptr)) {
		cout << "Parent and child are not allowed to be null" << endl << flush;
	}
	/* Check for cyclic references */
	else if (parent == child) {
		cout << "Parent and child are not allowed to point to the same node !!!"
				<< endl;
		cout << "parent: " << parent->AsString() << endl;
		cout << "child: " << child->AsString() << endl;
		cout << endl << flush;
	}
	/* Check if parent node is managed by this tree */
	else if (!isManagedNode(root, parent)) {
		cout << "Parent is not managed by this tree" << endl << flush;
	}
	/* Check if child already managed by this tree */
	else if (isManagedNode(root, child)) {
		cout << "Child already managed by this tree" << endl << flush;
	}
	/* set as first child if no first child present */
	else if (parent->getFirstChild() == nullptr) {
		parent->setFirstChild(child);
		size++;
	}
	/* insert as new first child and move current first child to next sibling of new first child */
	else {
		child->setNextSibling(parent->getFirstChild());
		parent->setFirstChild(child);
		size++;
	} /* if */
} /* Tree::insertChild */

void Tree::deleteSubTree(Node* node) {
	bool isRoot = false;
	Node* tmp = nullptr;

	/* Error if instance is not managed */
	if (!isManagedNode(root, node)) {
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
				tmp->setFirstChild(node->getNextSibling());
			}
			/* Cut from sibling list if found there */
			else if ((tmp = getFormerNeighbour(root, node)) != nullptr) {
				tmp->setNextSibling(tmp->getNextSibling()->getNextSibling());
			} /* if */
			/* need to remove reference because otherwise would be deleted along with the node */
			node->setNextSibling(nullptr);
		}/* if */

		/* delete the sub tree */
		delete node;
		node = nullptr;

		/* re initialize if it is root */
		if (isRoot) {
			clear();
		} else {
			size = countNodes(root);
		}/* if */
	} /* if */
} /* Tree::deleteSubTree */

void Tree::deleteElements() {
	deleteSubTree(root);
} /* Tree::deleteElements */

void Tree::clear() {
	root = nullptr;
	size = 0;
} /* Tree::clear */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
void Tree::print(ostream & os) const {
	Node* node = root;
	vector<Node*> firstLevel;
	map<int, vector<Node*>> leveledMap;

	/* header including root node */
	os << "##################################################" << endl;
	os << "node count: " << size << endl;
	os << "##################################################" << endl;
	os << "Level: 0" << endl;
	os << "Parent: (root has not parent)" << endl;
	os << "Nodes: " << *root << endl << endl;

	/* build root map for each level under root */
	node = root;
	firstLevel.push_back(root);
	leveledMap.insert(pair<int, vector<Node*>>(1, firstLevel));
	buildLeveledMap(node, 2, leveledMap);

	/* iterate over each level */
	map<int, vector<Node*>>::iterator it = leveledMap.begin();
	while (it != leveledMap.end()) {
		os << "-----------------------------------------------------" << endl;
		os << "Level: " << it->first << endl;
		os << "-----------------------------------------------------" << endl;

		/* print all nodes and their parents of the current level */
		vector<Node*>::iterator parentIterator = it->second.begin();
		while (parentIterator != it->second.end()) {
			os << "Parent: " << **parentIterator << endl;
			os << "        ";
			node = (*parentIterator)->getFirstChild();
			while (node != nullptr) {
				os << *node;
				if (node->getNextSibling() != nullptr) {
					os << " - ";
				} /* if */
				node = node->getNextSibling();
			} /* while */
			parentIterator++;
			cout << endl;
		} /* while */

		os << endl << flush;
		it++;
	} /* while */
} /* Tree::print */

////////////////////////////////////////////////////////////
// Operators                                              //
////////////////////////////////////////////////////////////
ostream& operator<<(ostream & os, const Tree & tree) {
	tree.print(os);
	return os;
} /* operator<< */

Tree & Tree::operator=(const Tree & other) {
	if (this != &other) {
		/* delete current root */
		if (root != nullptr) {
			delete root;
		} /* if */
		root = other.getRoot()->clone();
		size = other.getSize();
	} /* if */
	return *this;
} /* Tree::operator= */
