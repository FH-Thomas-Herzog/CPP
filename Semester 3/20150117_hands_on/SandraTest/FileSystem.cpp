#include <iostream>
#include <string.h>
#include <string>


#include "FileSystem.h"
#include "Directory.h"
#include "File.h"
#include "FSNode.h"


using namespace std;

/* constructor calls constructor of Tree*/
FileSystem::FileSystem() {
  Tree();
}

FileSystem::~FileSystem() {
  //dtor
}

void FileSystem::addNode(FSNode* n, FSNode* parent) {
  cout << "FSaddNode" << endl;
  //if no root is defined, set root first
  if(!this->getRoot()) {
    this->setRoot(n);
    return;
  }

  if(!n) {
    cout << "ERROR file does not exist." << endl;
    return;
  }

  FSNode *tmpNode = this->findNode(parent->getName(), this->getRoot());
  if(tmpNode == nullptr) {
    cout << "ERROR path does not exist" << endl;
    return;
  }

  FSNode *firstChild = tmpNode->getFirstChild();
  //if parent has no first child, add as first child first
  if(!firstChild) {
    //this->insertChild(parent, n);
    parent->setFirstChild(n);
  } else {
    //set n as first sibling
    FSNode *nextSibling = firstChild->getNextSibling();
    if(!nextSibling) {
      firstChild->setNextSibling(n);
    } else {
      // find last sibling and add n as nextSibling
      FSNode *lastSibling = firstChild->getLastSibling(firstChild);
      lastSibling->setNextSibling(n);
    }
  }
}

FSNode* FileSystem::findNode(const string& name, FSNode* start) const {
  cout << "FileSystem::findNode" << endl;
  if ((!start) || (name == "")) {
    return nullptr;
  }

  if((start->getName().compare(name)) == 0) {
    return start;
  }
  FSNode *firstChild = start->getFirstChild();
  cout << (start->getName() == name) << endl;
  if((firstChild->getName() == name) == 0) {
    return firstChild;
  }

    FSNode *sibling = firstChild->getNextSibling();
    while(sibling) {
      cout << sibling->getName().compare(name)  << endl;

      if(sibling->getName().compare(name) == 0) {
        cout << "return" << endl;
        return sibling;
      }
      sibling = sibling->getNextSibling();
    }

  this->findNode(name, firstChild->getFirstChild());
}

FSNode* FileSystem::getRoot() {
  return (FSNode *)Tree::getRoot();
}

void FileSystem::setRoot(FSNode *n) {
  Tree::setRoot(n);
}


string FileSystem::getLastDir(const string& path) {
  cout << "getLastDir" << endl;
  //convert string to char*
  std::string sPath = path; //cout << "sPath = " << sPath << endl; cout << "path = " << path << endl;
  char *givenPath = strdup(path.c_str());
  //cout << "givenPath: " << givenPath << endl;

  const char *separator = "/ ";
  char *lastDir = "";
  char *next = strtok(givenPath, separator);

  while(next) {
    lastDir = next;
    //cout << "while lastDir: " << lastDir << endl;
    next = strtok(NULL, separator);
  }
  //cout << "lastDir: " << lastDir << endl;
  int length = sizeof(lastDir)/sizeof(char);
  std::string result(lastDir, length);

  delete[] givenPath;
  cout << "result: " << result << endl;

  return result;
}

/* create or insert in directory by calling method addNode
   in: path, dirname
   */
void FileSystem::mkdir(const string& path, const string& dirname) {
  cout << "method mkdir" << endl;
  FSNode *newDir = new Directory(dirname);
  string parentName;

  if(path != "") {
    parentName = getLastDir(path);
  } else {
    parentName = "";
  }

  //cout << "parentName = " << parentName << endl;
  FSNode *parent = findNode(parentName, this->getRoot());
  this->addNode(newDir, parent);
}

/* create or insert in file by calling method addNode
   in: path, dirname
   */
void FileSystem::touch(const string& path, const string& filename) {
  cout << "FileSystem::touch" << endl;
  FSNode *newFile = new File(filename);
  string parentName;

  if(path != "") {
    parentName = getLastDir(path);
  } else {
    parentName = "";
  }

  FSNode *parent = findNode(parentName, this->getRoot());
  cout << "::touch | parent: " << *parent << endl;
  this->addNode(newFile, parent);
}

void FileSystem::rm(const string& path, const string& filename) {
  FSNode *node = findNode(filename, this->getRoot());
  this->deleteElement(node);
}


void FileSystem::rmdir(const string& path, const string& dirname) {
  FSNode *node = findNode(dirname, this->getRoot());
  this->deleteSubtree(node);
}

void FileSystem::ls() const {
  if(!this->Tree::getRoot()) {
    cout << "ERROR FileSystem is empty" << endl;
  } else {
    Tree::print(cout);
  }
}


