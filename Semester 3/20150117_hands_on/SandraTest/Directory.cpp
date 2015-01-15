#include "Directory.h"

/* constructor */
Directory::Directory(const string &name) : FSNode(nullptr, nullptr, name) {
  cout << "init Directory" << endl;
}

/* destructor */
Directory::~Directory() {

}
