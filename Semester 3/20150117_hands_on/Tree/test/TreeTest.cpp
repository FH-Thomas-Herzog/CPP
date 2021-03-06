/*
 * TreeTest.h
 * This is the implementation of the tree tests.
 *
 *  Created on: Dec 23, 2014
 *      Author: Thomas Herzog
 */
#include "TreeTests.h"
#include "MetaInfo.h"

using namespace std;
using namespace ML;

void make_suite_TreeTests(cute::suite* s) {
	(*s).push_back(CUTE(test_insertChild_null_parent));
	(*s).push_back(CUTE(test_insertChild_null_child));
	(*s).push_back(CUTE(test_insertChild_unmanaged_parent));
	(*s).push_back(CUTE(test_insertChild_unmanaged_child));
	(*s).push_back(CUTE(test_clear));
	(*s).push_back(CUTE(test_deleteElements));
	(*s).push_back(CUTE(test_deleteElements));
	(*s).push_back(CUTE(test_clear));
	(*s).push_back(CUTE(test_deleteSubtree_child));
	(*s).push_back(CUTE(test_deleteSubtree_root));
	(*s).push_back(CUTE(test_deleteSubtree_sibling));
	(*s).push_back(CUTE(test_tree_example));
	(*s).push_back(CUTE(test_print_example));
	(*s).push_back(CUTE(test_copy_constructor));
	(*s).push_back(CUTE(test_assign_operator));
}

void test_insertChild_null_parent() {
	Tree* tree = new Tree((*new Node()));
	Node* child = new Node();
	tree->insertChild(nullptr, child);

	ASSERT_EQUAL(1, tree->getSize());

	delete child;
	delete tree;
}

void test_insertChild_null_child() {
	Tree* tree = new Tree((*new Node()));
	Node* parent = new Node();
	tree->insertChild(parent, nullptr);

	ASSERT_EQUAL(1, tree->getSize());

	delete parent;
	delete tree;
}

void test_insertChild_unmanaged_parent() {
	Node* root = new Node();
	Tree* tree = new Tree(*root);
	Node* unmanaged = new Node();
	Node* newChild = new Node();

	tree->insertChild(tree->getRoot(), new Node());
	Node* n3 = new Node();
	tree->insertChild(tree->getRoot(), n3);
	Node* n2 = new Node();
	tree->insertChild(tree->getRoot(), n2);

	tree->insertChild(n2, new Node());
	tree->insertChild(n2, new Node());

	Node* n4 = new Node();
	tree->insertChild(n3, new Node());
	tree->insertChild(n3, new Node());
	tree->insertChild(n3, n4);
	tree->insertChild(unmanaged, newChild);

	delete unmanaged;
	delete newChild;
	delete tree;
}

void test_insertChild_unmanaged_child(){
	Node* root = new Node();
	Tree* tree = new Tree(*root);
	Node* newChild = new Node();

	tree->insertChild(tree->getRoot(), new Node());
	Node* n3 = new Node();
	tree->insertChild(tree->getRoot(), n3);
	Node* n2 = new Node();
	tree->insertChild(tree->getRoot(), n2);

	tree->insertChild(n2, new Node());
	tree->insertChild(n2, new Node());

	Node* n4 = new Node();
	tree->insertChild(n3, new Node());
	tree->insertChild(n3, new Node());
	tree->insertChild(n3, n4);
	tree->insertChild(n3, n4);

	delete newChild;
	delete tree;
}

void test_clear() {
	Tree* tree = new Tree((*new Node()));
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());

	Node* root = tree->getRoot();
	tree->clear();

	ASSERT_EQUAL(0, tree->getSize());

	delete root;
	delete tree;
}

void test_deleteElements() {
	Tree* tree = new Tree((*new Node()));
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());

	tree->deleteElements();

	ASSERT_EQUAL(0, tree->getSize());

	delete tree;
}

void test_deleteSubtree_root() {
	Tree* tree = new Tree((*new Node()));
	Node* subParent = new Node();
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), subParent);
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(subParent, new Node());
	tree->insertChild(subParent, new Node());
	tree->insertChild(subParent, new Node());

	tree->deleteSubTree(tree->getRoot());
	ASSERT_EQUAL(0, tree->getSize());
	delete tree;
}

void test_deleteSubtree_child() {
	Tree* tree = new Tree((*new Node()));
	Node* l1 = new Node();
	Node* l2 = new Node();
	Node* l3 = new Node();

	tree->insertChild(tree->getRoot(), l1);
	tree->insertChild(l1, l2);
	tree->insertChild(l2, l3);
	tree->insertChild(l2, new Node());
	tree->insertChild(l2, new Node());
	tree->insertChild(l2, new Node());

	tree->deleteSubTree(l2);
	ASSERT_EQUAL(2, tree->getSize());
	delete tree;
}

void test_deleteSubtree_sibling() {

	Tree* tree = new Tree((*new Node()));
	Node* subParent = new Node();
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), subParent);
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(subParent, new Node());
	tree->insertChild(subParent, new Node());
	tree->insertChild(subParent, new Node());

	tree->deleteSubTree(subParent);
	ASSERT_EQUAL(3, tree->getSize());
	delete tree;
}

void test_tree_example() {
	Node* root = new IntNode(1);
	Tree* tree = new Tree(*root);

	tree->insertChild(tree->getRoot(), new IntNode(4));
	Node* n3 = new IntNode(3);
	tree->insertChild(tree->getRoot(), n3);
	Node* n2 = new IntNode(2);
	tree->insertChild(tree->getRoot(), n2);

	tree->insertChild(n2, new IntNode(5));
	tree->insertChild(n2, new IntNode(6));

	tree->insertChild(n3, new IntNode(7));
	tree->insertChild(n3, new IntNode(8));
	tree->insertChild(n3, new IntNode(9));
	tree->insertChild(n3, new IntNode(10));

	cout << *tree << endl << flush;

	delete tree;
}

void test_print_example() {

	Node* root = new IntNode(1);
	Tree* tree = new Tree(*root);

	Node* n2 = new IntNode(2);
	tree->insertChild(tree->getRoot(), n2);
	Node* n3 = new IntNode(3);
	tree->insertChild(tree->getRoot(), n3);
	tree->insertChild(tree->getRoot(), new IntNode(4));

	tree->insertChild(n2, new IntNode(5));
	tree->insertChild(n2, new IntNode(6));

	tree->insertChild(n3, new IntNode(7));
	tree->insertChild(n3, new IntNode(8));
	tree->insertChild(n3, new IntNode(9));
	tree->insertChild(n3, new IntNode(10));

	cout << *tree << endl << flush;

	delete tree;
}

void test_copy_constructor() {

	Tree tree(new IntNode(1));
	Tree tr(tree);

	tree.insertChild(tree.getRoot(), new IntNode(4));
	Node* n3 = new IntNode(3);
	tree.insertChild(tree.getRoot(), n3);
	Node* n2 = new IntNode(2);
	tree.insertChild(tree.getRoot(), n2);

	tree.insertChild(n2, new IntNode(5));
	tree.insertChild(n2, new IntNode(6));

	tree.insertChild(n3, new IntNode(7));
	tree.insertChild(n3, new IntNode(8));
	tree.insertChild(n3, new IntNode(9));
	tree.insertChild(n3, new IntNode(10));

	cout << "Original tree: " << endl;
	cout << tree << endl;

	cout << "Copying tree via copy constructor" << endl;
	Tree copied = tree;

	cout
			<< "Copied tree: (Deep copy no references are shared between instances)"
			<< endl;
	cout << copied;

	tree.deleteElements();
	copied.deleteElements();
}

void test_assign_operator() {
	Tree tree(new IntNode(1));

	tree.insertChild(tree.getRoot(), new IntNode(4));
	Node* n3 = new IntNode(3);
	tree.insertChild(tree.getRoot(), n3);
	Node* n2 = new IntNode(2);
	tree.insertChild(tree.getRoot(), n2);

	tree.insertChild(n2, new IntNode(5));
	tree.insertChild(n2, new IntNode(6));

	tree.insertChild(n3, new IntNode(7));
	tree.insertChild(n3, new IntNode(8));
	tree.insertChild(n3, new IntNode(9));
	tree.insertChild(n3, new IntNode(10));

	cout << "Copying the original tree by performing a copy via operator="
			<< endl;
	/* need to first declare otherwise copy constructor would be invoked */
	Tree referenced;
	/* Copy via assign operator */
	referenced = tree;

	cout << "Original tree:" << endl << tree << endl << flush;
	cout
			<< "Copied tree: (Deep copy no references are shared between instances)"
			<< endl << tree << endl << flush;

	tree.deleteElements();
	referenced.deleteElements();
}
