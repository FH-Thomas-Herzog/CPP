#ifndef hashtable_hpp
#define hashtable_hpp

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <climits>
#include <math.h>
#include <bitset>

using namespace std;

template<typename V, typename H, typename C>
class hashtable;

template<typename V, typename H, typename C>
std::ostream & operator << (std::ostream & os, const hashtable<V, H, C> &ht) {
  //TODO: replace with iterator
  bool first = true;
  for (list<V> valueList : ht.data) {
    for (V value : valueList) {
      if (! first) {
        os << ",";
      } else {
        first = false;
      }
      os << value;
    }
  }
  os << endl;
  return os;
}


template<typename V, typename H, typename C>
class hashtable {
  friend std::ostream & operator << <V, H, C>(std::ostream & os, const hashtable<V, H, C> &ht);

public:
  typedef V value_type;
  typedef H hash_function_type;
  typedef C key_equal_function_type;
  typedef unsigned int size_t;
  typedef value_type const * const_pointer;
  typedef value_type const & const_reference;
  typedef std::ptrdiff_t     difference_type;
  typedef const_pointer      pointer;
  typedef const_reference    reference;
  typedef std::size_t        size_type;

private:
  size_t n_buckets;
  hash_function_type hasher;
  key_equal_function_type equals;
  double max_load_factor;
  double min_load_factor;

  int actionsSinceLastRehash = 0;

  vector<list<value_type>> data;

  int hashIt(const V& value) {
    return hasher(value) % n_buckets;
  }
  void clearAndInit() {
    data.clear();
    data.resize(n_buckets);
  }
  void rehash() {
    double currentLoad = load_factor();
    if (min_load_factor > currentLoad && max_load_factor > currentLoad) {
      return; // skip when no rehash is needed
    }
    rehash(nextPrime(size() * 2));
    cout << capacity() << endl;
  }

public:
  int nextPrime(int value) {
    int n = 1000;
    while (true) {
      if (INT_MAX / 10 < n) { // prevent integer overflow
        return INT_MAX;
      }
      n *= 10;
      vector<bool> noPrime(n + 1);  //vector<bool> is especially optimized in STL
      for (int i = 2; i <= n; i++) {
        noPrime[i] = false;
      }
      for (int i = 2; i < sqrt(n); i++) {
        if (! noPrime[i]) {
          if (i > value) {
            return i;
          }
          for (int j = i * i; j <= n; j += i) {
            noPrime[j] = true;
          }
        }
      }
    }
  }

  hashtable(size_t n_buckets = 10,
            hash_function_type hasher = std::hash<V>(),
            key_equal_function_type equals = std::equal_to<V>(),
            double max_load_factor = 0.8,
            double min_load_factor = 0.2) :
              n_buckets(n_buckets),
              hasher(hasher),
              equals(equals),
              max_load_factor(max_load_factor),
              min_load_factor(min_load_factor) {
                clearAndInit();
              };
  virtual ~hashtable() {
    // nothing to do
  }

  void insert(const V &value) {
    // only rehash if more than capacity() / 2 insertions have happened before
    if (actionsSinceLastRehash > (capacity() / 2)) {
      actionsSinceLastRehash = 0;
      rehash();
    }
    list<string>& valueList = data[hashIt(value)];
    if (find(valueList.begin(), valueList.end(), value) == valueList.end()) {
        valueList.push_front(value);
    }
    actionsSinceLastRehash++;
  }
  void erase(const V &value) {
    list<string>& valueList = data[hashIt(value)];
    if (find(valueList.begin(), valueList.end(), value) != valueList.end()) {
        valueList.remove(value);
    }
    rehash();
  }
  bool contains(const V &value) const {
    bool ret = false;
    list<string> valueList = data[hashIt(value)];
    if (find(valueList.begin(), valueList.end(), value) != valueList.end()) {
      ret = true;
    }
    return ret;
  }
  void rehash(size_t new_n_buckets) {
    n_buckets = new_n_buckets;
    vector<list<value_type>> oldData(data);
    clearAndInit();
    //TODO: replace with iterator
    for (list<value_type> valueList : oldData) {
      for (value_type value : valueList) {
        insert(value);
      }
    }
  }
  double load_factor() const {
    return ((double)n_buckets) / ((double)size());
  }
  size_t size() const {
    return accumulate(data.begin(), data.end(), 0,
                        [] (int sum, const list<V>& l) {
                          return sum + l.size();
                        });
  }
  size_t capacity() {
    // return the vector's capacity because a different modulo calculation could lead to a better balanced hashtable
    return n_buckets;
  }
  bool empty() const {
    return size() == 0;
  }
/*
  bool operator == (const hashtable &other) const;
*/
  typedef std::iterator <std::bidirectional_iterator_tag,
                         value_type,
                         difference_type,
                         const_pointer,
                         const_reference> iterator_base;

  class const_iterator : public iterator_base {
  public:
    typedef typename iterator_base::difference_type   difference_type;
    typedef typename iterator_base::iterator_category iterator_category;
    typedef typename iterator_base::pointer           pointer;
    typedef typename iterator_base::reference         reference;
    typedef typename iterator_base::value_type        value_type;
  private:
    vector<list<value_type>> data;
    int capacity;
    typename vector<list<value_type>>::const_iterator dataIterator;
    typename list<value_type>::const_iterator currentListIterator;
  public:

    const_iterator(vector<list<value_type>> data, int capacity) : data(data), capacity(capacity) {
      for (auto it = data.begin(); it != data.end(); it++) {
        for (auto itit = it->begin(); itit != it->end(); itit++) {
          cout << *itit << endl;
        }
      }
      dataIterator = data.begin();
      currentListIterator = dataIterator->begin();
      currentListIterator++;
      while (currentListIterator == dataIterator->end() && dataIterator != data.end()) {
        dataIterator++;
        currentListIterator = dataIterator->begin();
      }
      currentListIterator++;
      while (currentListIterator == dataIterator->end() && dataIterator != data.end()) {
        dataIterator++;
        currentListIterator = dataIterator->begin();
      }
      currentListIterator++;
      while (currentListIterator == dataIterator->end() && dataIterator != data.end()) {
        dataIterator++;
        currentListIterator = dataIterator->begin();
      }
/*      currentListIterator = data[currentIndex].begin();
      if (currentListIterator == data[currentIndex].end()) {
        ++*this;
      }*/
    }

    bool operator == (const_iterator const & rhs) const {
      bool ret = true;
      if (rhs.dataIterator != dataIterator) {
        ret = false;
      }
      if (rhs.currentListIterator != currentListIterator) {
        ret = false;
      }
      return ret;
    }
    bool operator != (const_iterator const & rhs) const {
      return ! (rhs == *this);
    }

    reference operator * () const {
      return *currentListIterator;
    }
    pointer   operator -> () const {
      return &*currentListIterator;
    }

    const_iterator & operator ++ () {
/*      if (currentListIterator == data[currentIndex].end()) {
        if (currentIndex < capacity - 1) {
          currentIndex++;
          currentListIterator = data[currentIndex].begin();
        }
      } else {
        cout << "A before: " << *currentListIterator << endl;
        cout << "listsize: " << data[currentIndex].size() << endl;
      cout << "C1: " << (currentListIterator == data[currentIndex].end() ? "true" : "false") << endl;
        currentListIterator++;
      cout << "C2: " << (currentListIterator == data[currentIndex].end() ? "true" : "false") << endl;
        cout << "A after: " << *currentListIterator << endl;
      }

      if (currentIndex < capacity && currentListIterator == data[currentIndex].end()) {
        ++*this;
      }
      return *this;*/
      currentListIterator++;
      while (currentListIterator == dataIterator->end() && dataIterator != data.end()) {
        dataIterator++;
        currentListIterator = dataIterator->begin();
      }
      return *this;
    }
/*    const_iterator & operator -- () {
    }
*/
/*    const_iterator operator ++ (int) {
      const_iterator res(*this);
      ++(*this);
      return res;
    }
    const_iterator operator -- (int) {
      const_iterator res(*this);
      --(*this);
      return res;
    }*/
  };

  typedef const_iterator iterator;

  const_iterator begin() const {
    return const_iterator(data, (int)n_buckets);
  }
  const_iterator end() const {
    return begin();
//    return (const_iterator*)nullptr;
  }
/*
  iterator cbegin();
  iterator cend();
  const_iterator cbegin() const;
  const_iterator cend() const;
*/
};

template<typename V, typename H, typename C>
std::ostream & operator << (std::ostream & os, const hashtable<V, H, C> &ht);

#endif // hashtable_hpp
