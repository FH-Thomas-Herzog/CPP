#include "FSNode.h"

/* constructor */
FSNode::FSNode(FSNode *firstChild, FSNode *nextSibling, const string &name): Node(firstChild, nextSibling)  {
  cout << "ctor // FSNode " << endl;
  this->name = name;
}

/* destructor */
FSNode::~FSNode() {
  this->~Node();
}

/* getFirstChild returns pointer to firstChild
   out: FSNode *firstChild
   */
FSNode* FSNode::getFirstChild() const {
  return (FSNode *)Node::getFirstChild();
}

/* getNextSibling returns pointer to nextSibling
   out: FSNode *nextSibling
   */
FSNode* FSNode::getNextSibling() const {
  return (FSNode *)Node::getNextSibling();
}


FSNode* FSNode::getLastSibling(FSNode* fsn) const {
  FSNode *next = fsn->getNextSibling();
  FSNode *result;

  if(!next) {
    return fsn;
  } else {
    while(next) {
      result = next;
      next = next->getNextSibling();
    }
    return result;
  }
}

string FSNode::getName() const {
  return name;
}

void FSNode::setFirstChild(FSNode* n) {
  Node::setFirstChild(n);
}

void FSNode::setNextSibling(FSNode* n) {
  Node::setNextSibling(n);
}

void FSNode::print(std::ostream& os) const {
  os << this->name;

  if(this->getNextSibling()) {
    os << " ---> ";
    this->getNextSibling()->print(os);
  } else {
    os << endl;
  }
  if(this->getFirstChild()){
    os << this->name << ": ";
    this->getFirstChild()->print(os);
  }
}

void FSNode::printNode(std::ostream& os) const {
  os << this->name;
}

ostream& operator<<(ostream &os, const FSNode &fsn) {
  fsn.printNode(os);
  return os;
}
