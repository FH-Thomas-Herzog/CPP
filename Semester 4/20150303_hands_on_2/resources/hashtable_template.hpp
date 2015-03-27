#ifndef hashtable_hpp
#define hashtable_hpp

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>

template<typename V, typename H, typename C>
class hashtable;

template<typename V, typename H, typename C>
std::ostream & operator << (std::ostream & os, const hashtable<V, H, C> &ht);


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

  hashtable(size_t n_buckets = 10,
            hash_function_type hasher = std::hash<V>(),
            key_equal_function_type equals = std::equal_to<V>(),
            double max_load_factor = 0.8,
            double min_load_factor = 0.2);
  virtual ~hashtable() {}

  void insert(const V &value);
  void erase(const V &value);
  bool contains(const V &value) const;
  void rehash(size_t new_n_buckets);
  double load_factor() const;
  size_t size() const;
  size_t capacity();
  bool empty() const;
  bool operator == (const hashtable &other) const;

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

    bool operator == (const_iterator const & rhs) const;
    bool operator != (const_iterator const & rhs) const;

    reference operator *  () const;
    pointer   operator -> () const;

    const_iterator & operator ++ ();
    const_iterator & operator -- ();

    const_iterator operator ++ (int);
    const_iterator operator -- (int);
    
  };

  typedef const_iterator iterator;
  
  const_iterator begin() const;
  const_iterator end() const;

  iterator cbegin();
  iterator cend();
  const_iterator cbegin() const;
  const_iterator cend() const;

};

template<typename V, typename H, typename C>
std::ostream & operator << (std::ostream & os, const hashtable<V, H, C> &ht);

#endif // hashtable_hpp
