#include <iostream>

#include "Tree.h"
#include "IntNode.h"
#include "FileSystem.h"


using namespace std;

int main() {
/*
  cout << ".:: TEST PROGRAM ::." << endl;
  Tree *t = new Tree();

  //add Nodes to tree & insertChild
  cout << "TREE under construction..." << endl;
  IntNode *n1 = new IntNode(1);
  t->addNode(n1);

  IntNode *n2 = new IntNode(2);
  IntNode *n3 = new IntNode(3);
  IntNode *n4 = new IntNode(4);
  IntNode *n5 = new IntNode(5);
  IntNode *n6 = new IntNode(6);
  IntNode *n7 = new IntNode(7);
  IntNode *n8 = new IntNode(8);
  IntNode *n9 = new IntNode(9);
  IntNode *n10 = new IntNode(10);

  t->addNode(n2, n1);
  t->addNode(n3, n1);
  t->addNode(n4, n1);
  t->addNode(n5, n2);
  t->addNode(n6, n2);
  t->addNode(n7, n3);
  t->addNode(n8, n3);
  t->addNode(n9, n3);
  t->addNode(n10, n3);
  cout << endl;

  // print tree
  cout << "PRINT TREE" << endl;
  cout << *t << endl;

  //getRoot
  cout << "ROOT OF TREE is: " << *t->getRoot() << endl;

  //sizeOfTree
  cout << "SIZE OF TREE = " << t->getSize(t->getRoot()) << " nodes." << endl;

  //copyContructor
  cout << "COPY CONSTRUCTOR" << endl;
  Tree *tCopy = new Tree(*t);
  cout << *tCopy << endl;

  //assignmentOperator
  cout << "ASSIGNMEN OPERATOR" << endl;
  Tree *tAss = new Tree();
  *tAss = *t;
  cout << *tAss << endl;

  //deleteSubtree
  cout << "deleteSubtree" << endl;
  t->deleteSubtree(n6); //should not work --> use deleteElement
  t->deleteSubtree(n3); cout << *t << endl;

  //sizeOfTree
  cout << "SIZE OF TREE = " << t->getSize(t->getRoot()) << " nodes." << endl;

  //deleteElement - does not work yet
  cout << "DELETE ELEMENT" << endl;
  t->deleteElement(n5); cout << *t << endl;
  t->deleteElement(n2); cout << *t << endl;
  cout << endl;

  //add previous node but with missing parent node
  cout << "try to add n6 as child from n2" << endl;
  t->addNode(n6, n2); cout << endl;


  //deleteTree
  cout << "CLEAR TREE" << endl;
  t->clearTree();
  cout << *t << endl;

  //tCopy->clearTree();
  //cout << *tCopy << endl;

  //tAss->clearTree();
  //cout << *tAss << endl; //does not work
*/
  /* ================================================================= */

  cout << ".:: TEST PROGRAM FILE SYSTEM ::." << endl;
  FileSystem *fs = new FileSystem();
  fs->mkdir("", "root");
  fs->touch("root", "ReadMe.txt");
  fs->mkdir("root", "bin");
  //fs->touch("root/bin", "a.exe");
  //cout << "touch2" << endl; fs->touch("root/bin", "a.exe");
  //cout << "touch3" << endl; fs->touch("root/bin", "b.exe");
  fs->ls();
  //fs->rm("root/bin", "a.exe");
  //cout << "rmdir1" << endl;fs->rmdir("", "root"); // -> ERROR: dir not empty
  //cout << "ls2" << endl; fs->ls();
  //fs->rm("root/bin", "b.exe");
  //fs->rmdir("", "root/bin");
  //cout << "ls2" << endl;fs->ls();
  fs->rm("root", "ReadMe.txt");
  cout << "ls3" << endl;fs->ls();
  fs->rmdir("", "root");
  fs->ls();
  delete fs;
  fs->ls();

  return 0;
}
