#include <iostream>

#include "Tree.h"

using namespace std;

/* constructor: inits tree */
Tree::Tree() {
  cout << "init Tree // ctor" << endl;
  this->root = nullptr;
}

/* destructor deletes root element */
Tree::~Tree() {
  cout << "destructor" << endl;
  delete this->root;
  this->root = nullptr;
}

/* copy constructor
   in: reference of original tree
   */
Tree::Tree(const Tree& orig) {
/*
  if(orig.root) {
    this->root = new IntNode(orig.root->getValue());
  } else {
    this->root = nullptr;
  }
*/
}

/* assignment operator
   in: reference of other tree
   out: reference of tree
   */
Tree& Tree::operator=(const Tree &other) {
/*
  if(this == &other) {
    return *this;
  } else {
    if(this->root){
      delete this->root;
    }
    if(other.root) {
      this->root = new IntNode(*other.root);
    } else {
      this->root = nullptr;
    }
  } */
}

/* addNode insert new Nodes in tree
   in: new Node n, root Node parent
   */
void Tree::addNode(Node* n, Node *parent) {
  //if no root is defined, set root first
  if(!this->root) {
    this->setRoot(n);
    return;
  }

  if(!n) {
    cout << "ERROR nothing to add." << endl;
    return;
  }

  Node *tmpNode = this->findNode(parent, this->root);
  if(tmpNode == nullptr) {
    cout << "ERROR parent node is not in tree" << endl;
    return;
  }

  Node *firstChild = tmpNode->getFirstChild();
  //if parent has no first child, add as first child first
  if(!firstChild) {
    this->insertChild(parent, n);
  } else {
    //set n as first sibling
    Node *nextSibling = firstChild->getNextSibling();
    if(!nextSibling) {
      firstChild->setNextSibling(n);
    } else {
      // find last sibling and add n as nextSibling
      Node *lastSibling = firstChild->getLastSibling(firstChild);
      lastSibling->setNextSibling(n);
    }
  }
}

/* findNode searches node n in tree beginning from start
   in: node n, start node
   out: node
   */
Node* Tree::findNode(Node* n, Node* start) const {
  if(!start) {
    return nullptr;
  }

  if(start == n) {
    return n;
  }

  Node *firstChild = start->getFirstChild();
  if(firstChild == n) {
    return n;
  } else {
    Node *sibling = firstChild->getNextSibling();
    while(sibling) {
      if(sibling == n) {
        return n;
      }
      sibling = sibling->getNextSibling();
    }
  }
  this->findNode(n, firstChild->getFirstChild());
}

/* insertChild sets the reference to child not in the parent node
   in: Node *parent, Node *child
   */
void Tree::insertChild(Node* parent, Node* child) {
  parent->setFirstChild(child);
}

/* getRoot returns root note of tree
   out: root
   */
Node* Tree::getRoot() const {
  return this->root;
}

void Tree::setRoot(Node *n) {
  this->root = n;
}

/* deletes sub elements of a given node, but does not delete sub root */
void Tree::deleteSubtree(Node *node) {
  Node *firstChild = node->getFirstChild();

  if(!firstChild) {
    cout << "ERROR node is no parent node. Can not delete subtree." << endl;
    return;
  } else {
    Node *sibling = firstChild->getNextSibling();
    Node *next;
    while(sibling) {
      if(sibling->getFirstChild()) {
        deleteSubtree(sibling);
      }
      next = sibling->getNextSibling();

      if(next) {
        firstChild->setNextSibling(next);
      } else {
        firstChild->setNextSibling(nullptr);
      }
      sibling = firstChild->getNextSibling();
    }

    if(firstChild->getFirstChild()) {
      deleteSubtree(firstChild);
    } else {
      node->setFirstChild(nullptr);
      delete firstChild;
    }
  }
}

int Tree::getSize(Node *n) const {
  if(!this->root) {
    //tree is empty
    return 0;
  }

  Node *firstChild = n->getFirstChild();
  int result = 1;

  if(!firstChild) {
    //tree only contains root node
    return result;
  } else {
    result = result + this->getSize(firstChild);

    Node *sibling = firstChild->getNextSibling();
    while(sibling) {
      result++;
      if(sibling->getFirstChild()) {
        return result + this->getSize(sibling);
      }
      sibling = sibling->getNextSibling();
    }
    return result;
  }
}

/* clearTree deletes all subtrees beginning from root and calls destructor */
void Tree::clearTree() {
  this->deleteSubtree(this->root);
  this->~Tree();
}

/* deleteElement reomves specific Node
   in: Node *n
   */
void Tree::deleteElement(Node *n) {
  if(n == this->root) {
    this->clearTree();
    return;
  }

  //delete subtree first, if n is a parent node
  Node *child = n->getFirstChild();
  if(child) {
    deleteSubtree(n);
  }

  Node *pred = getPredecessor(n, this->root);
  Node *predChild = pred->getFirstChild();
  Node *next = n->getNextSibling();

  if(predChild == n) {
    pred->setFirstChild(next);
  } else {
    pred->setNextSibling(next);
  }

  n->setFirstChild(nullptr);
  n->setNextSibling(nullptr);
  delete n;
  n = nullptr;
}

/* */
Node* Tree::getPredecessor(Node *n, Node *start) const {
  Node *firstChild = start->getFirstChild();

  if(firstChild == n) {
    return start;
  } else {
    //search in siblings
    Node *sibling = firstChild->getNextSibling();
    Node *tmpNode;
    while(sibling) {
      if(sibling == n) {
        return start;
      }
      if(sibling->getFirstChild()) {
        tmpNode = this->getPredecessor(n, sibling);
        if(tmpNode) {
          return tmpNode;
        }
      }
      sibling = sibling->getNextSibling();
    }
  }
  return this->getPredecessor(n, start->getFirstChild());
}

/* prints tree and it's nodes */
void Tree::print(std::ostream& os) const {
  this->root->print(os);
}

/* overload output operator */
ostream& operator<<(ostream &os, const Tree &t) {
  if(t.root == nullptr) {
    os << "tree is empty - nothing to print" << endl;
    return os;
  }

  t.print(os);
  return os;
}














