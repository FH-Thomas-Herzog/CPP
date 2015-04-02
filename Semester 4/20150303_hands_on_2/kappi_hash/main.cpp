#include "hashtable_template.hpp"

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  hashtable<string, std::hash<string>, std::equal_to<string>> theTable(3);
  theTable.insert(string("a"));
  theTable.insert(string("b"));
  theTable.insert(string("c"));
  theTable.insert(string("d"));
  theTable.insert(string("e"));
  theTable.insert(string("a1"));
  theTable.insert(string("b1"));
  theTable.insert(string("c1"));
  theTable.insert(string("d1"));
  theTable.insert(string("e1"));

  theTable.erase(string("d1"));

//  cout << theTable << endl;
  cout << "Hello world!" << endl;
  auto b = theTable.begin();
  cout << "asdf" << endl;
  cout << *b << endl;
  ++b;
  cout << *b << endl;
  return 0;
  copy(b, theTable.end(), ostream_iterator<string>(cout, ", "));
  return 0;

}
