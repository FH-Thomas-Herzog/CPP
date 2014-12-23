#include "TreeTests.h"

cute::suite make_suite_TreeTests() {
	cute::suite s;
	s.push_back(CUTE(test_insertChild_null_parent));
	s.push_back(CUTE(test_insertChild_null_child));
	s.push_back(CUTE(test_insertChild_unmanaged_parent));
	return s;
}

void test_insertChild_null_parent() {
	Tree* tree = new Tree();
	Node* child = new Node();
	tree->insertChild(nullptr, child);

	ASSERT_EQUAL(tree->getRoot()->getFirstChild(), nullptr);
	ASSERT_EQUAL(tree->getRoot()->getNextSbiling(), nullptr);

	delete child;
	delete tree;
}

void test_insertChild_null_child() {
	Tree* tree = new Tree();
	Node* parent = new Node();
	tree->insertChild(parent, nullptr);

	ASSERT_EQUAL(tree->getRoot()->getFirstChild(), nullptr);
	ASSERT_EQUAL(tree->getRoot()->getNextSbiling(), nullptr);

	delete parent;
	delete tree;
}

void test_insertChild_unmanaged_parent() {
	Tree* tree = new Tree();
	Node* parent = new Node();
	Node* child = new Node();
	tree->insertChild(parent, child);

	ASSERT_NOT_EQUAL_TO(tree->getRoot(), parent);
	ASSERT_EQUAL(tree->getRoot()->getFirstChild(), nullptr);
	ASSERT_EQUAL(tree->getRoot()->getNextSbiling(), nullptr);

	delete parent;
	delete child;
	delete tree;
}

