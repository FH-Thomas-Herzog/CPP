#include "Entry.h"

#include <iomanip>
#include <ostream>
#include <iterator>

using namespace std;

Entry::Entry(string w) : word(w) {}

Entry::~Entry() {}

void Entry::addLineNr(int lnr) {
  lineNrs.insert(lnr);
}

bool Entry::operator < (const Entry &e) const {
  return word < e.word;
}

ostream & operator << (ostream &os, const Entry &e) {
  os << setw(15) << e.word << ": ";
  copy(e.lineNrs.begin(), e.lineNrs.end(), ostream_iterator<int>(os, ","));
  return os;
}
