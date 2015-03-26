#ifndef SCOPED_PTR_HPP_INCLUDED
#define SCOPED_PTR_HPP_INCLUDED

#include <stdlib.h>
#include <stdio.h>

template<typename T>
class scoped_ptr {

private:
  T* ptr;

public:
  typedef T value_type;

  explicit scoped_ptr(T *ptr = nullptr) : ptr(ptr) { }

  // NOTE: descturctor not virtual as we don't intend to every derive from it
  ~scoped_ptr() { delete ptr; }

  void reset(T *ptr = nullptr) {
    if (this->ptr != ptr) {
      delete this->ptr;
      this->ptr = ptr;
    }
  }

  T& operator * () const { return *ptr; }
  T* operator ->() const { return  ptr; }
     operator T*() const { return  ptr; }

  T* get() const { return ptr; }

  // variant 1: auto_ptr behaviour: grab the other's pointer
// #ifdef VARIANT_1
  scoped_ptr(scoped_ptr &sp) {
    ptr = sp.ptr;
    sp.ptr = nullptr;
  }

  scoped_ptr& operator = (const scoped_ptr &sp) {
    delete ptr;
    ptr = sp.ptr;
    sp.ptr = nullptr;
  }
// #endif // VARIANT_1

  // variant 2: prevent copying alltogether
  // scoped_ptr(const scoped_ptr &) = delete;
  // scoped_ptr& operator = (const scoped_ptr &) = delete;

};



#endif // SCOPED_PTR_HPP_INCLUDED
