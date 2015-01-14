#ifndef FSNODE_H
#define FSNODE_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class FSNode : public Node {
  private:
    string name;
  public:
    FSNode(FSNode *firstChild = nullptr, FSNode *nextSibling = nullptr, const string &name = "");
    virtual ~FSNode();

    virtual FSNode* getFirstChild() const;
    virtual FSNode* getNextSibling() const;
    virtual FSNode* getLastSibling(FSNode *fsn) const;
    virtual string getName() const;
    virtual void setFirstChild(FSNode *n);
    virtual void setNextSibling(FSNode *n);
    virtual void print(std::ostream &os) const;
    virtual void printNode(std::ostream &os) const;

    friend std::ostream &operator << (std::ostream &os, const FSNode &fsn);

};

#endif // FSNODE_H
