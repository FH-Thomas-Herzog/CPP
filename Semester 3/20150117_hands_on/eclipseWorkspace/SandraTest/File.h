#ifndef FILE_H
#define FILE_H

#include "FSNode.h"


class File : public FSNode {
  private:
    Node* const firstChild = nullptr;
  public:
    File(const string& name);
    virtual ~File();


};

#endif // FILE_H
