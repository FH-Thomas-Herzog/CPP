#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Tree.h"
#include "FSNode.h"
#include "Directory.h"


class FileSystem : public Tree {
  private:


  public:
    FileSystem();
    virtual ~FileSystem();

    virtual void addNode(FSNode *n, FSNode *parent = 0);
    virtual FSNode* findNode(const string& name, FSNode *start) const;
    virtual FSNode* getRoot();
    virtual void setRoot(FSNode *n);
    virtual string getLastDir(const string& path);

    virtual void mkdir(const string &path, const string &dirname); // create new directory
    virtual void touch(const string &path, const string &filename); // create new file
    virtual void rm(const string &path, const string &filename); // remove file
    virtual void rmdir(const string &path, const string &dirname); // remove directory
    virtual void ls() const; // list file system contents

};

#endif // FILESYSTEM_H