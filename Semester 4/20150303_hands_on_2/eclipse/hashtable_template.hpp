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
std::ostream & operator <<(std::ostream & os, const hashtable<V, H, C> &ht) {
	int bucketCount = 1;
	os << "Hashtable content:" << endl;
	for_each(ht.table.begin(), ht.table.end(),
			([&bucketCount, &os ](const list<string>& values) {
				stringstream ss;
				ss << "bucket " << bucketCount << ".";
				os << ss.str() << endl;
				int i = 0;
				int valuesSize = values.size();
				for_each(values.begin(), values.end(), ([&os, &valuesSize, &i](const string& value) {
									os << value;
									if((i+1) < valuesSize) {
										os << " - ";
									}
									i++;
								}));
				os << endl << endl;
				bucketCount++;
			}));
	return os;
}

template<typename V, typename H, typename C>
class hashtable {
	friend std::ostream & operator <<<V, H, C>(std::ostream & os,
			const hashtable<V, H, C> &ht);

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

	int actionsSinceLastRehash = 0;

	vector<list<value_type>> table;

	int calculateHashIdx(const V& value) const {
		return hasher(value) % currentCapacity;
	}

	void clear() {
		table.clear();
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
			valueList.push_front(value);
		}
		table[idx] = valueList;
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
		size_t size = 0;
		for_each(table.begin(), table.end(),
				([&size](const list<value_type> values) {
					size += values.size();
				}));
		return size;
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
		int idx = 0;
		const vector<list<value_type>>& table;
		list<string> values;
		typename list<value_type>::const_iterator listIt;
	public:
		const_iterator(const vector<list<value_type>>& table,
				bool isEnd = false) :
				table(table) {
			if (!isEnd) {
				values = table.at(idx);
				listIt = values.begin();
			} else {
				idx = (table.size() - 1);
				values = table.at(idx);
				listIt = values.end();
			}
		}

		bool operator ==(const_iterator const & rhs) const {
			return (idx == rhs.idx) && (listIt == rhs.listIt);
		}
		bool operator !=(const_iterator const & rhs) const {
			return (idx != rhs.idx) && (listIt != rhs.listIt);
		}

		reference operator *() const {
			return *listIt;
		}

		pointer operator ->() const {
			return listIt;
		}

		const_iterator & operator ++() {
			// List still has elements
			if (listIt != values.end()) {
				listIt++;
			}
			// End reached therefore start form new
			else if (idx == (table.size() - 1)) {
				idx = 0;
				values = table[idx];
				listIt = values.begin();
			}
			// list end reached
			else {
				idx++;
				values = table[idx];
				listIt = values.begin();
			}
			return (*this);
		}

		const_iterator & operator --() {
			// List still has elements
			if (listIt != values.begin()) {
				listIt--;
			}
			// End reached therefore start form new
			else if (idx == 0) {
				idx = (table.size() - 1);
				values = table[idx];
				listIt = values.end();
			}
			// list end reached
			else {
				idx--;
				values = table[idx];
				listIt = values.end();
			}
			return (*this);
		}

		const_iterator operator ++(int) {
			const_iterator res(*this);
			++(*this);
			return res;
		}
		const_iterator operator --(int) {
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
};

template<typename V, typename H, typename C>
std::ostream & operator <<(std::ostream & os, const hashtable<V, H, C> &ht);

#endif // hashtable_hpp
