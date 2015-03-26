#include "person.h"
#include <iostream>
#include <string>

using namespace std;

person::person() {
  cout << "INFO: person()" << endl;
}

person::person(std::string first_name, std::string last_name)
  : first_name(first_name), last_name(last_name) {
  cout << "INFO: person(" << first_name << ", " << last_name << ")" << endl;
}

person::person(const person &p)
  : first_name(p.first_name), last_name(p.last_name) {
  cout << "INFO: person(" << first_name << ", " << last_name << ") - copy constructor" << endl;
}

person::~person() {
  cout << "INFO: ~person(" << first_name << ", " << last_name << ")" << endl;
}

bool person::operator<(const person &p) const {
  return last_name < p.last_name ||
         (last_name == p.last_name && first_name < p.first_name);
}

void person::print(ostream &os) const {
  os << first_name << ' ' << last_name;
}

void person::read(istream &is) {
  is >> first_name >> last_name;
}

ostream& operator << (ostream &os, const person &p) {
  p.print(os);
  return os;
}

istream& operator >> (istream &is, person &p) {
  p.read(is);
  return is;
}
