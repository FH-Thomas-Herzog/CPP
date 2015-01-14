#ifndef TREE_H
#define TREE_H

#include <sstream>

#include "IntNode.h"

using namespace std;

class Tree {
  protected:
    Node *root;
  public:
    Tree(); //ctor
    virtual ~Tree(); //dtor
    Tree(const Tree &orig); // copy constructor
    Tree& operator=(const Tree &other); // assignment operator

    virtual void addNode(Node *n, Node *parent = 0);
    virtual Node* findNode(Node *n, Node *start) const;
    virtual Node* getPredecessor(Node *n, Node *start) const;

    virtual Node* getRoot() const;
    virtual void setRoot(Node *n);

    virtual void insertChild(Node *parent, Node *child);
    virtual void deleteSubtree(Node *n);
    virtual int getSize(Node *n) const;
    virtual void clearTree();
    virtual void deleteElement(Node *n);
    virtual void print(std::ostream &os) const;

    friend std::ostream &operator << (std::ostream &os, const Tree &t);

};

#endif // TREE_H