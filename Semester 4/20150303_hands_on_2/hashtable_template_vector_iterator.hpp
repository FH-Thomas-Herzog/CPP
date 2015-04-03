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
#include <algorithm>
#include <sstream>

using namespace std;

template<typename V, typename H, typename C>
class hashtable;

/**
 * Overloaded output operator
 */
template<typename V, typename H, typename C>
std::ostream & operator <<(std::ostream & os, hashtable<V, H, C> &ht) {
	int cnt = 1;
	auto beginIt = ht.begin();
	auto endIt = ht.end();
	for (auto it = ht.begin(); it != ht.end(); it++) {
		cout << (*it) << endl << flush;
	}
//	for_each(beginIt, endIt,
//			([&cnt, &ht, &os](const string value) {
//				os << "hash-key: " << ht.calculateHashIdx(value) << " - " << value << endl;
//			}));

	return os;
}

template<typename V, typename H, typename C>
class hashtable {
	friend std::ostream & operator <<<V, H, C>(std::ostream & os,
			hashtable<V, H, C> &ht);

public:
	typedef V value_type;
	typedef H hash_function_type;
	typedef C key_equal_function_type;
	typedef unsigned int size_t;
	typedef value_type const * const_pointer;
	typedef value_type const & const_reference;
	typedef std::ptrdiff_t difference_type;
	typedef const_pointer pointer;
	typedef const_reference reference;
	typedef std::size_t size_type;

private:
	size_t currentCapacity;
	hash_function_type hasher;
	key_equal_function_type equals;
	double maxLoadFactor;
	double minLoadFactor;
	const int MIN_CAPACITY = 10;
	int elementCount = 0;
	vector<value_type> iteratorValues;
	bool modified = true;

	vector<list<value_type>> table;

	vector<value_type>& prepareForIterator() {
		if (modified) {
			int i = 0;
			iteratorValues.clear();
			iteratorValues.resize(size());
			for_each(table.begin(), table.end(),
					([this, &i](const list<value_type>& l) {
						if(!l.empty()) {
							for_each(l.begin(), l.end(), ([this, &i](const value_type& value) {
												iteratorValues[i] = value;
												i++;
											}));
						}
					}));
			modified = false;
		}
		return iteratorValues;
	}

	int calculateHashIdx(const V& value) const {
		return hasher(value) % currentCapacity;
	}

	void clear() {
		table.clear();
		modified = true;
		if (currentCapacity < MIN_CAPACITY) {
			currentCapacity = MIN_CAPACITY;
		}
		table.resize(currentCapacity);
	}

	void validateForReHash() {
		double currentLoad = load_factor();
		double factor = 0;
		if ((currentLoad < minLoadFactor)
				&& ((currentCapacity * 0.5) > MIN_CAPACITY)) {
			factor = 0.5;
		} else if (currentLoad > maxLoadFactor) {
			factor = 1.5;
		}

		if (factor != 0) {
			rehash(currentCapacity * factor);
		}
	}

public:

	/**
	 * Default constructor which initializes all members but the buckets.
	 */
	hashtable(size_t n_buckets = 10, hash_function_type hasher = std::hash<V>(),
			key_equal_function_type equals = std::equal_to<V>(),
			double max_load_factor = 0.8, double min_load_factor = 0.2) :
			currentCapacity(n_buckets), hasher(hasher), equals(equals), maxLoadFactor(
					max_load_factor), minLoadFactor(min_load_factor) {
		clear();
	}

	/**
	 * No dynamic members therefore nothing to do.
	 */
	virtual ~hashtable() {
		// nothing to do
	}

	/**
	 * Inserts the value in the given list if this value is not managed by this list. Does nothing otherwise.
	 * @param:
	 * 		const V& value: the value to inserted
	 */
	void insert(const V &value) {
		validateForReHash();
		size_t idx = calculateHashIdx(value);
		list<string> valueList = table[idx];
		if (find(valueList.begin(), valueList.end(), value)
				== valueList.end()) {
			table[idx].push_front(value);
			elementCount++;
			modified = true;
		}
	}

	/**
	 * Deletes the value from the hashtable if this value is managed by this hashtable. Does nothing otherwise.
	 * @param:
	 * 		const V& value: the value to be removed from the hastable
	 */
	void erase(const V &value) {
		size_t idx = calculateHashIdx(value);
		list<string>& valueList = table[idx];
		auto it = find(valueList.begin(), valueList.end(), value);
		if (it != valueList.end()) {
			valueList.remove(value);
			modified = true;
		}
		validateForReHash();
	}

	/**
	 * Answers tthe question if this hashtable contains the given value
	 * @param
	 * 		const V& value: the values to be searched in the table
	 * @return
	 * 		true if this value is managed by this hastable, false otherwise
	 */
	bool contains(const V &value) const {
		size_t idx = calculateHashIdx(value);
		list<string> valueList = table[idx];
		auto it = find(valueList.begin(), valueList.end(), value);
		return (it != valueList.end());
	}

	/**
	 * Rehashes the hashtable entries and rebuilds the map with the new has indexes
	 * @param:
	 * 		the new buckets
	 */
	void rehash(size_t new_n_buckets) {
		currentCapacity = new_n_buckets;
		elementCount = 0;
		modified = true;
		vector<list<value_type>> oldData(table);
		clear();
		for_each(oldData.begin(), oldData.end(),
				([this](const list<value_type> values) {
					for_each(values.begin(), values.end(), ([this](const string value) {
										insert(value);
									}));
				}));
	}

	/**
	 * Gets the current load factor
	 * @return
	 * 		the current load factor
	 */
	double load_factor() const {
		size_t curSize = size();
		return (curSize > 0) ? ((double) (currentCapacity) / (size())) : 0.0;
	}

	/**
	 * Gets the current size.
	 * @return
	 * 		the current size
	 */
	size_t size() const {
		return elementCount;
	}

	/**
	 * Returns the current capacity
	 * @return
	 * 		the current capacity
	 */
	size_t capacity() {
		return currentCapacity;
	}

	/**
	 * Answers the question if this hashtable is empty
	 * @return
	 * 		true if this instance has no entries, false otherwise
	 */
	bool empty() const {
		return size() == 0;
	}

	/**
	 * hashtables are logically equal if the fit one of the following requirements.
	 * 1. Same instance
	 * 2. Other instance
	 * 		a. Same size
	 * 		b. Contain same elements
	 *
	 * @param
	 * 		const hashtable& other: the other instance to compare with
	 * @return
	 * 		true if the hastables are logically equal, false otherwise
	 */
	bool operator ==(const hashtable &other) const {
		bool result = false;
		// same instance
		if (this == (&other)) {
			result = true;
		}
		// Other instance has same size
		else if (size() == other.size()) {
			int i = 0;
			result = true;
			// check if other contains same elements
			while ((result) && (i < other.table.size())) {
				result = contains(other.table[i]);
			}
		}
		// not same instance and not same size
		else {
			result = false;
		}

		return result;
	}

	typedef std::iterator<std::bidirectional_iterator_tag, value_type,
			difference_type, const_pointer, const_reference> iterator_base;

	/**
	 * The hashtable iterator class
	 */
	class const_iterator: public iterator_base {
	public:
		typedef typename iterator_base::difference_type difference_type;
		typedef typename iterator_base::iterator_category iterator_category;
		typedef typename iterator_base::pointer pointer;
		typedef typename iterator_base::reference reference;
		typedef typename iterator_base::value_type value_type;
	private:
		vector<value_type>& values;
		typename vector<value_type>::const_iterator it;
	public:
		const_iterator(hashtable<V, H, C> ht, bool isEnd = false) :
				values(ht.prepareForIterator()) {
			if (!isEnd) {
				it = values.begin();
			} else {
				it = values.end();
			}
		}

		bool operator ==(const_iterator const & hsIt) const {
			return it == hsIt.it;
		}
		bool operator !=(const_iterator const & hsIt) const {
			if (it == values.end()) {
				if (it != hsIt.it) {
					cout << "end not recognized";
				}
			}
			return it != hsIt.it;
		}

		reference operator *() const {
			return *it;
		}

		pointer operator ->() const {
			return it;
		}

		/**
		 * Increments the iterator if elements are left. Will do nothing is no elements are left.
		 * @return
		 * 		this iterator instance
		 */
		const_iterator & operator ++() {
			// List still has elements
			if (it != values.end()) {
				it++;
			}else {
				cout << "no increment possible";
			}
			return (*this);
		}

		/**
		 * Decrements the iterator if elements are left. Will do nothing is no elements are left.
		 * @return
		 * 		this iterator instance
		 */
		const_iterator & operator --() {
			// List still has elements
			if (it != values.begin()) {
				it--;
			}
			return (*this);
		}

		/**
		 * @see const_iterator & operator ++()
		 */
		const_iterator operator ++(int) {
			++(*this);
			return (*this);
		}

		/**
		 * @see const_iterator & operator --()
		 */
		const_iterator operator --(int val) {
			--(*this);
			return (*this);
		}
	};

	typedef const_iterator iterator;

	const_iterator begin() {
		return const_iterator((*this));
	}
	const_iterator end() {
		return const_iterator((*this));
	}
};

template<typename V, typename H, typename C>
std::ostream & operator <<(std::ostream & os, const hashtable<V, H, C> &ht);

#endif // hashtable_hpp
