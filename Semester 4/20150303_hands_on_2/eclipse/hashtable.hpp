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
	for_each(ht.table.begin(), ht.table.end(),
			([&ht, &os](const list<V>& l) {
				for_each(l.begin(), l.end(), ([&ht, &os](const V& value) {
									os << "hash-key: " << ht.calculateHashIdx(value) << " - " << value << endl << flush;
								}));
			}));
	return os;
} /* operator << */

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
	int elementCount = 0;
	vector<list<value_type>> table;

	/**
	 * This method calculates the hash index for the bakced table depending on the current set capacity.
	 * @param
	 * 		const V& value: the value to calculates hash index for
	 * @return
	 * 		the calculated hash index
	 */
	int calculateHashIdx(const V& value) const {
		return hasher(value) % currentCapacity;
	} /* calculateHashIdx */

	/**
	 * Validates if an rehash of the backed values is necessary.
	 */
	void validateForReHash() {
		double currentLoad = load_factor();
		double factor = 0;
		if ((currentLoad < minLoadFactor)
				&& ((currentCapacity * 0.5) > MIN_CAPACITY)) {
			factor = 0.5;
		} else if (currentLoad > maxLoadFactor) {
			factor = 1.5;
		} /* if */

		if (factor != 0) {
			rehash(currentCapacity * factor);
		} /* if */
	} /* validateForReHash */

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
	} /* hashtable */

	/**
	 * No dynamic members therefore nothing to do.
	 */
	virtual ~hashtable() {
		// nothing to do
	} /* ~hashtable */

	void clear() {
		elementCount = 0;
		table.clear();
		if (currentCapacity < MIN_CAPACITY) {
			currentCapacity = MIN_CAPACITY;
		} /* if */
		table.resize(currentCapacity);
	} /* clear */

	/**
	 * Inserts the value in the given list if this value is not managed by this list. Does nothing otherwise.
	 * @param:
	 * 		const V& value: the value to inserted
	 */
	void insert(const V &value) {
		validateForReHash();
		size_t idx = calculateHashIdx(value);
		if (find(table[idx].begin(), table[idx].end(), value)
				== table[idx].end()) {
			table[idx].push_front(value);
			elementCount++;
		} /* if */
	} /* insert */

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
			elementCount--;
		} /* if */
		validateForReHash();
	} /* erase */

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
	} /* contains */

	/**
	 * Rehashes the hashtable entries and rebuilds the map with the new has indexes
	 * @param:
	 * 		the new buckets
	 */
	void rehash(size_t newCapacity) {
		currentCapacity = newCapacity;
		vector<list<value_type>> oldData(table);
		table.clear();
		table.resize(currentCapacity);
		for_each(oldData.begin(), oldData.end(),
				([this](const list<value_type> values) {
					for_each(values.begin(), values.end(), ([this](const string value) {
										size_t idx = calculateHashIdx(value);
										table[idx].push_front(value);
									}));
				}));
	} /* rehash */

	/**
	 * Gets the current load factor
	 * @return
	 * 		the current load factor
	 */
	double load_factor() const {
		size_t curSize = size();
		return (curSize > 0) ? ((double) (size()) / (currentCapacity)) : 0.0;
	} /* load_factor */

	/**
	 * Gets the current size.
	 * @return
	 * 		the current size
	 */
	size_t size() const {
		return elementCount;
	} /* size */

	/**
	 * Returns the current capacity
	 * @return
	 * 		the current capacity
	 */
	size_t capacity() {
		return currentCapacity;
	} /* capacity */

	/**
	 * Answers the question if this hashtable is empty
	 * @return
	 * 		true if this instance has no entries, false otherwise
	 */
	bool empty() const {
		return size() == 0;
	} /* empty */

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
				auto it = other.table[i].begin();
				while ((result) && (it != other.table[i].end())) {
					result = contains((*it));
					it++;
				} /* while */
				i++;
			} /* while */
		} /* if */

		return result;
	} /* operator== */

	typedef std::iterator<std::bidirectional_iterator_tag, value_type,
			difference_type, const_pointer, const_reference> iterator_base;

	/**
	 * The hashtable iterator class
	 * NOT WORKING AT ALL !!!!!!!!!!!!!!!!!!!!!!!!!
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
		const bool isEnd;
		const bool reverse;
		typename list<value_type>::const_iterator listIt;

		void prepareIterator() {
			if (isEnd) {
				idx = (table.size() - 1);
				values = table.at(idx);
				listIt = values.end();
				if (reverse) {
					setNextIterator();
				}
			} else {
				idx = 0;
				values = table.at(idx);
				listIt = values.begin();
				if (!reverse) {
					setNextIterator();
				}
			}
		}

		void setNextIterator() {
			if (isEnd) {
				while ((idx != 0) && (listIt == values.begin())) {
					idx--;
					values = table.at(idx);
					listIt = values.end();
				}
			} else {
				while ((idx != (table.size() - 1)) && (listIt == values.end())) {
					idx++;
					values = table.at(idx);
					listIt = values.begin();
				}
			}
		}

	public:
		const_iterator(const vector<list<value_type>>& table,
				bool isEnd = false, bool reverse = false) :
				table(table), isEnd(isEnd), reverse(reverse) {
			prepareIterator();
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
			if ((listIt != values.end()) && (idx < table.size())) {
				idx++;
				values = table[idx];
				listIt = values.begin();
				setNextIterator();
			}
			return (*this);
		}

		const_iterator & operator --() {
			// List still has elements
			if (listIt != values.begin()) {
				listIt--;
			}
			// list end reached
			if ((listIt != values.begin()) && (idx != 0)) {
				idx--;
				values = table[idx];
				listIt = values.end();
				setNextIterator();
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
	} /*begin */

	const_iterator end() const {
		return const_iterator(table, true);
	} /* end */

	const_iterator rbegin() const {
		return const_iterator(table, false, true);
	} /* rbegin */

	const_iterator rend() const {
		return const_iterator(table, true, true);
	} /* rend */
};


#endif // hashtable_hpp