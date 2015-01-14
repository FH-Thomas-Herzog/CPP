#ifndef NODE_H
#define NODE_H

#include <sstream>

using namespace std;

class Node {
  private:
    Node *firstChild, *nextSibling;
    //int id;
  public:
    explicit Node(Node *firstChild = nullptr, Node *nextSibling = nullptr);
    virtual ~Node();
    //Node(const Node &orig); // copy constructor
    virtual Node& operator=(const Node &other); // assignment operator

    virtual Node* getFirstChild() const;
    virtual Node* getNextSibling() const;
    virtual Node* getLastSibling(Node *n) const;
    virtual void setFirstChild(Node *n);
    virtual void setNextSibling(Node *n);
    virtual void print(std::ostream &os) const;
    virtual void printNode(std::ostream &os) const;

    friend std::ostream &operator << (std::ostream &os, const Node &n);
  };

#endif // NODE_H
