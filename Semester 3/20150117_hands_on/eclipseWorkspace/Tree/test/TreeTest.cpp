#include "TreeTests.h"
#include "MetaInfo.h"

using namespace std;
using namespace ML;

cute::suite make_suite_TreeTests() {
	cute::suite s;
	s.push_back(CUTE(test_insertChild_null_parent));
	s.push_back(CUTE(test_insertChild_null_child));
	s.push_back(CUTE(test_insertChild_unmanaged_parent));
	s.push_back(CUTE(test_clear));
	s.push_back(CUTE(test_deleteElements));
	s.push_back(CUTE(test_insertChild_null_child));
	s.push_back(CUTE(test_insertChild_unmanaged_parent));
	s.push_back(CUTE(test_deleteElements));
	s.push_back(CUTE(test_clear));
	s.push_back(CUTE(test_deleteSubtree_child));
	s.push_back(CUTE(test_deleteSubtree_root));
	s.push_back(CUTE(test_deleteSubtree_sibling));
	s.push_back(CUTE(test_tree_example));
	s.push_back(CUTE(test_print_example));
	s.push_back(CUTE(test_copy_constructor));
	s.push_back(CUTE(test_assign_operator));
	return s;
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
	Tree* tree = new Tree((*new Node()));
	Node* parent = new Node();
	Node* child = new Node();
	tree->insertChild(parent, child);

	ASSERT_EQUAL(1, tree->getSize());

	delete parent;
	delete child;
	delete tree;
}

void test_clear() {
	Tree* tree = new Tree((*new Node()));
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());
	tree->insertChild(tree->getRoot(), new Node());

	Node* root = tree->getRoot();
	tree->clear();

	ASSERT_EQUAL(1, tree->getSize());
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

	ASSERT_EQUAL(1, tree->getSize());
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
	ASSERT_EQUAL(1, tree->getSize());
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

	delete tree;
}

void test_print_example() {

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

void test_copy_constructor() {

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

	cout << "Original tree: " << endl;
	cout << *tree << endl;

	cout << "Copying tree and deleting original" << endl;
	Tree* copied = new Tree(*tree);

	delete tree;

	cout
			<< "Copied tree: (Deep copy no references are shared between instances)"
			<< endl;
	cout << *copied;

	delete copied;
}

void test_assign_operator() {
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

	cout << "Unmodified Original tree: " << endl;
	cout << *tree << endl << endl;

	cout << "Referencing the same tree now" << endl;
	Tree referenced;
	referenced = *tree;

	cout << "Adding new node on referenced tree" << endl << endl;
	referenced.insertChild(referenced.getRoot(), new IntNode(-1));
	cout << "Original tree:" << endl << *tree << endl << endl;
	cout << "Referenced tree: " << endl << referenced << endl << flush;

	delete tree;

}
