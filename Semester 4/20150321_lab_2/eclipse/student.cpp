#include <string>
#include <iostream>
#include "student.h"

using namespace std;

student::student() {
  cout << "INFO: student()" << endl;
}

student::student(std::string first_name, std::string last_name, std::string registration_nr)
  : person(first_name, last_name), registration_nr(registration_nr) {
  cout << "INFO: student(" << first_name << ", " << last_name << ", " << registration_nr << ")" << endl;
}

student::student(const student& s)
  : person(s), registration_nr(s.registration_nr) {
  cout << "INFO: student(" << first_name << ", " << last_name << ", " << registration_nr
       << ") - copy constructor" << endl;
}

student::~student() {
  cout << "INFO: ~student(" << first_name << ", " << last_name << ", " << registration_nr << ")" << endl;
}

void student::print(std::ostream& os) const {
  person::print(os);
  os << ' ' << registration_nr;
}

void student::read(std::istream& is) {
  person::read(is);
  is >> registration_nr;
}
