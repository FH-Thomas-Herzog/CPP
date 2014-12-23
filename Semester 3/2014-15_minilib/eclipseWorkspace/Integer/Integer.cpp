#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <cassert>
#include "Integer.h"

using namespace std;
using namespace ML;

Integer::Integer(int value) : value(value) {
    cout << "Constructor Integer(" << value << ") called" << endl << flush;
    Register("Integer", "Object");
}

Integer::~Integer() {
    cout << "Destructor ~Integer() called" << endl << flush;
}

string Integer::asString() const {
    stringstream ss;
    ss << value;
    return ss.str();
}

Integer::operator int() const {
    return value;
}

int Integer::getVal() {
    return value;
}

int Integer::setVal() {
    this->value = value;
}

bool Integer::IsEqualTo(const Object* o) const {
    const Integer* i = dynamic_cast<const Integer*>(o);
    if(i == nullptr) {
        return false;
    }
    return i->value == value;
}

bool Integer::IsLessThen(const Object* o) const {
    assert(o->IsA("*Integer*"));
    const Integer* i = dynamic_cast<const Integer*>(o);
    return i->value < value;
}

istream& operator>> (istream& is, Integer& input) {
    is >> input.value;
    return is;
}
