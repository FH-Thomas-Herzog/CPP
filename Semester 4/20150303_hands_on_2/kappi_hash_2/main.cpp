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

  hashtable<string, std::hash<string>, std::equal_to<string>> theTable2(3);
  theTable2.insert(string("a"));
  theTable2.insert(string("b"));
  theTable2.insert(string("c"));
  theTable2.insert(string("d"));
  theTable2.insert(string("e"));
  theTable2.insert(string("a1"));
  theTable2.insert(string("b1"));
  theTable2.insert(string("c1"));
  theTable2.insert(string("d1"));
  theTable2.insert(string("e1"));

//  theTable2.erase(string("d1"));

  cout << "EQUAL: " << (theTable == theTable2 ? "true" : "false") << endl;

//  cout << theTable << endl;
  cout << "Hello world!" << endl;
//  hashtable<string, std::hash<string>, std::equal_to<string>>::const_iterator b = theTable.begin();
  cout << "asdf" << endl;
  for (auto it = theTable.begin(); it != theTable.end(); ++it) {
    cout << *it << ", ";
  }
  cout << endl;
  cout << "fdsa" << endl;
  for (string value : theTable) {
    cout << value << ", ";
  }
  cout << endl;
  cout << "franz" << endl;
  copy(theTable2.begin(), theTable2.end(), ostream_iterator<string>(cout, ", "));
  cout << endl;

  auto beginning = theTable.begin();
  auto ending = theTable.end();
  cout << "beginning: " << *beginning << endl;
  cout << "++ending: " << *(++ending) << endl;
  auto ending2 = theTable.end();
  ending2++;
  cout << "ending++: " << *ending2 << endl;

  return 0;

}
