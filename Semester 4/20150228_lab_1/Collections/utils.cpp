#include "utils.hpp"

#include <string>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

// auxiliary functions
// isalpha does not work for umlauts etc.
// convert interfaces e.g. int ispunct(int)
// STL is strict on interfaces
bool isPunct(char ch) { return static_cast<bool>(ispunct(ch)); }
bool isDigit(char ch) { return static_cast<bool>(isdigit(ch)); }
bool isAlpha(char ch) { return static_cast<bool>(isalpha(ch)); }

char toLower(char ch) { return static_cast<char>(tolower(ch)); }

string normalize(string word) {
  string::iterator newEnd;
  newEnd = remove_if(word.begin(), word.end(), isPunct);
  newEnd = remove_if(word.begin(), newEnd, isDigit);
  word.erase(newEnd, word.end());
  transform(word.begin(), word.end(), word.begin(), toLower);
  return word;
}

void openStream(int argc, char *argv[], ifstream &fin) {
  if (argc < 2) {
    cerr << "usage: " << argv[0] << " filename" << endl;
    exit(-1);
  }
  // ifstream fin(argv[1]); -> automatic variable, file closed on return
  fin.open(argv[1]);
  if (fin.fail()) { // same as operator!() tests both failbit and badbit
    cerr << "file " << argv[1] << " not found" << endl;
    exit(-2);
  }
  // fin returned as reference argument
}
