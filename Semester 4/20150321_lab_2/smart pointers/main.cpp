#include <iostream>
#include <set>
#include <iterator> // ostream_iterator
#include <algorithm> // for_each
#include <memory> // unique_ptr, shared_ptr

#include "person.h"
#include "student.h"
#include "scoped_ptr.hpp"
#include "counted_ptr.hpp"
// #include "ext_counted_ptr.hpp"

using namespace std;

static void static_collection_test() {
}

static void simple_pointer_test() {
}

static void scoped_pointer_test() {
}

static void unique_pointer_test() {
}

static void counted_pointer_test() {
}

static void shared_pointer_test() {
}

int main() {
  cout << "============================\n"
       << "===== collection tests =====\n"
       << "============================\n" << endl;

  cout << "----- static objects -----" << endl;
  static_collection_test();
  cout << "==========================\n" << endl;

  cout << "----- simple pointers -----" << endl;
  simple_pointer_test();
  cout << "===========================\n" << endl;

  cout << "----- scoped pointers -----" << endl;
  scoped_pointer_test();
  cout << "===========================\n" << endl;

  cout << "----- unique pointers (STL) -----" << endl;
  unique_pointer_test();
  cout << "=================================\n" << endl;

  cout << "----- counted pointers -----" << endl;
  counted_pointer_test();
  cout << "============================\n" << endl;

  cout << "----- shared pointers (STL) -----" << endl;
  shared_pointer_test();
  cout << "=================================\n" << endl;

}
