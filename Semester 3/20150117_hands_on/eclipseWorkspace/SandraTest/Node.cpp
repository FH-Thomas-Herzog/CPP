#include <iostream>

#include "Node.h"

using namespace std;

/* constructor node */
Node::Node(Node *firstChild, Node *nextSibling) {
  this->firstChild = firstChild;
  this->nextSibling = nextSibling;
}

/* copy constructor */
/*
Node::Node(const Node& orig) {
  this->id = orig.id;
}
*/

/* overlaod assignment operator */
Node& Node::operator=(const Node& other) {
  if(this != &other) {
    this->firstChild = other.firstChild;
    this->nextSibling = other.nextSibling;
    //this->id = other.id;
  }
  return *this;
}

/* destructor deletes pointer to firstChild and nextSibling */
Node::~Node() {
  delete firstChild;
  this->firstChild = nullptr;
  delete nextSibling;
  this->nextSibling = nullptr;

}

/* getFirstChild returns pointer to firstChild
   out: Node *firstChild
   */
Node* Node::getFirstChild() const {
  return this->firstChild;
}

/* getNextSibling returns pointer to nextSibling
   out: Node *nextSibling
   */
Node* Node::getNextSibling() const {
  return this->nextSibling;
}

/* getLastSibling returns the lastSibling for a given Node
   in: Node *n
   out: Node* last Sibling
   */
Node* Node::getLastSibling(Node *n) const {
  Node *next = n->getNextSibling();
  Node *result;

  if(!next) {
    return n;
  } else {
    while(next) {
      result = next;
      next = next->getNextSibling();
    }
    return result;
  }
  //return result;
}

/* setFirstChild sets pointer to firstChild for a given Node
   in: Node *n
   */
void Node::setFirstChild(Node* n) {
  this->firstChild = n;
}

/* setNextSibling sets pointer to nextSibling for a given Node
   in: Node *n
   */
void Node::setNextSibling(Node* n) {
  this->nextSibling = n;
}

/* print nodes by iterating through nextSiblings and firstChild
   in: ostream& os
  */
void Node::print(std::ostream& os) const {
  /*
  os << this->id;

  if(this->nextSibling) {
    os << " ---> ";
    this->nextSibling->print(os);
  } else {
    os << endl;
  }
  if(this->firstChild){
    os << this->id << ": ";
    this->firstChild->print(os);
  }
  */
}

/* printNode returns the value of a single node
   in: ostream& os
   */
void Node::printNode(std::ostream& os) const {
  //os << this->id;
}

/* output operator calls printNode method
   in: ostream& os, Node &n
   out: os
   */
ostream& operator<<(ostream &os, const Node &n) {
  n.printNode(os);
  return os;
}

