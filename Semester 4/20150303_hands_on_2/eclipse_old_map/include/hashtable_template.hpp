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
  size_t currentCapacity;
  hash_function_type hasher;
  key_equal_function_type equals;
  double maxLoadFactor;
  double minLoadFactor;

  int actionsSinceLastRehash = 0;

  vector<list<value_type>> table;

  int calculateHashIdx(const V& value) const {
    return hasher(value) % currentCapacity;
  }
  void clear() {
    table.clear();
    table.resize(currentCapacity);
  }
  void validateForReHash() {
    double currentLoad = load_factor();
    if (minLoadFactor > currentLoad && maxLoadFactor > currentLoad) {
      return; // skip when no rehash is needed
    }
    rehash(nextPrime(size() * 2));
//    cout << capacity() << endl;
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
              currentCapacity(n_buckets),
              hasher(hasher),
              equals(equals),
              maxLoadFactor(max_load_factor),
              minLoadFactor(min_load_factor) {
                clear();
              };
  virtual ~hashtable() {
    // nothing to do
  }

  void insert(const V &value) {
    // only rehash if more than capacity() / 2 insertions have happened before
    if (actionsSinceLastRehash > (capacity() / 2)) {
      actionsSinceLastRehash = 0;
      validateForReHash();
    }
    list<string>& valueList = table[calculateHashIdx(value)];
    if (find(valueList.begin(), valueList.end(), value) == valueList.end()) {
        valueList.push_front(value);
    }
    actionsSinceLastRehash++;
  }
  void erase(const V &value) {
    list<string>& valueList = table[calculateHashIdx(value)];
    if (find(valueList.begin(), valueList.end(), value) != valueList.end()) {
        valueList.remove(value);
    }
    validateForReHash();
  }
  bool contains(const V &value) const {
    bool ret = false;
    list<string> valueList = table[calculateHashIdx(value)];
    if (find(valueList.begin(), valueList.end(), value) != valueList.end()) {
      ret = true;
    }
    return ret;
  }
  void rehash(size_t new_n_buckets) {
    currentCapacity = new_n_buckets;
    vector<list<value_type>> oldData(table);
    clear();
    for (list<value_type> valueList : oldData) {
      for (value_type value : valueList) {
        insert(value);
      }
    }
  }
  double load_factor() const {
    return ((double)currentCapacity) / ((double)size());
  }
  size_t size() const {
    return accumulate(table.begin(), table.end(), 0,
                        [] (int sum, const list<V>& l) {
                          return sum + l.size();
                        });
  }
  size_t capacity() {
    // return the vector's capacity because a different modulo calculation could lead to a better balanced hashtable
    return currentCapacity;
  }
  bool empty() const {
    return size() == 0;
  }

  bool operator == (const hashtable &other) const {
    bool ret = true;
    for (value_type value : other) {
      if (! contains(value)) {
        ret = false;
      }
    }
    return ret;
  }

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
    const vector<list<value_type>>& data;
    typename vector<list<value_type>>::const_iterator dataIterator;
    typename list<value_type>::const_iterator currentListIterator;
  public:
    const_iterator(const vector<list<value_type>>& pData, bool isEnd = false) : data(pData) {
      if (isEnd) {
        dataIterator = data.end();
      } else {
        dataIterator = data.begin();
        currentListIterator = dataIterator->begin();
        while (currentListIterator == dataIterator->end() && dataIterator != data.end()) {
          dataIterator++;
          if (dataIterator != data.end()) {
            currentListIterator = dataIterator->begin();
          }
        }
        if (dataIterator == data.end()) {
          isEnd = true;
        }
      }
    }

    bool operator == (const_iterator const & rhs) const {
      bool ret = true;
      if (rhs.dataIterator != dataIterator) {
        ret = false;
      } else if (dataIterator != data.end() && rhs.currentListIterator != currentListIterator) {
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
      if (dataIterator == data.end()) {
        dataIterator = data.begin();
        currentListIterator = dataIterator->begin();
      } else {
        currentListIterator++;
      }
      while (currentListIterator == dataIterator->end() && dataIterator != data.end()) {
        dataIterator++;
        if (dataIterator != data.end()) {
          currentListIterator = dataIterator->begin();
        }
      }
      return *this;
    }
    const_iterator & operator -- () {
      //TODO implement
    }

    const_iterator operator ++ (int) {
      const_iterator res(*this);
      ++(*this);
      return res;
    }
    const_iterator operator -- (int) {
      const_iterator res(*this);
      --(*this);
      return res;
    }
  };

  typedef const_iterator iterator;

  const_iterator begin() const {
    return const_iterator(table);
  }
  const_iterator end() const {
    return const_iterator(table, true);
  }

  iterator cbegin() {
    return begin();
  }
  iterator cend() {
    return end();
  }
  const_iterator cbegin() const {
    return begin();
  }
  const_iterator cend() const {
    return end();
  }
};

template<typename V, typename H, typename C>
std::ostream & operator << (std::ostream & os, const hashtable<V, H, C> &ht);

#endif // hashtable_hpp
