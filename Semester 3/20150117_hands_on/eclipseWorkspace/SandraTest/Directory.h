#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "FSNode.h"


class Directory : public FSNode {
  private:
  //no private data
  public:
    Directory(const string &name);
    virtual ~Directory();
};

#endif // DIRECTORY_H
