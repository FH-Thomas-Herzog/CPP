#ifndef HashTable_hpp
#define HashTable_hpp

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <vector>
#include <map>
#include <stdio.h>
#include <algorithm>

using namespace std;

template<typename V, typename H, typename C>
class HashTable;

//template<typename V, typename H, typename C>
//std::ostream & operator <<(std::ostream & os, const HashTable<V, H, C> &ht);

template<typename V, typename H, typename C>
class HashTable {
//		friend std::ostream & operator <<<V, H, C>(std::ostream & os,
//				const HashTable<V, H, C> &ht);

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
		//##############################################
		// Members
		//##############################################
		/**
		 * This container will realize the has table where the has key is mapped to a chain of elements.
		 * These chained elements are these elements which have the same hash key.
		 */
		map<size_t, vector<V&>, key_equal_function_type> hashTable;
		size_t currentSize;
		size_t currentCapacity;
		hash_function_type hasher;
		key_equal_function_type equals;
		double minLoadFactor;
		double maxLoadFactor;
		const double INCREASE_FACTOR = 0.5;
		const double DECREASE_FACTOR = 0.5;

		//##############################################
		// Private methods
		//##############################################
		/**
		 * Validates if the min/max load factor has been broken
		 */
		inline void validateLoadFactor() {
			double currentLoadFactor = load_factor();
			// Min load broken
			if (currentLoadFactor <= minLoadFactor) {
				// Cut table by half
				currentCapacity = (currentCapacity * INCREASE_FACTOR);
				rehash(currentCapacity);
			}
			// Max load broken
			else if (currentLoadFactor >= maxLoadFactor) {
				// Increase by 50%
				currentCapacity += (currentCapacity * DECREASE_FACTOR);
				rehash(currentCapacity);
			}
		}

		/**
		 * Calculates the has table index out of the calculated hash
		 * @param
		 * 		V& value: the value to get proper index for
		 * @return
		 * 		the calculates hash index for the hash table
		 */
		inline std::size_t calculateIndex(const V& value) {
			return (hasher(value) % currentCapacity);
		}

	public:
		inline HashTable(size_t n_buckets = 10, hash_function_type hasher =
				std::hash<V>(), key_equal_function_type equals =
				std::equal_to<V>(), double max_load_factor = 0.8,
				double min_load_factor = 0.2) :
				currentCapacity(n_buckets), hasher(hasher), equals(equals), minLoadFactor(
						min_load_factor), maxLoadFactor(max_load_factor), currentSize(
						0) {
			// Handle invalid capacity
			if (currentCapacity < 10) {
				currentCapacity = 10;
				cout << "Capacity of " << n_buckets
						<< " to small therefore set to default" << flush
						<< endl;
			}
			// HAndle invalid load factors
			if ((minLoadFactor >= maxLoadFactor) || (minLoadFactor <= 0)
					|| (maxLoadFactor >= 1)) {
				minLoadFactor = 0.2;
				maxLoadFactor = 0.8;
				cout
						<< "One of the load factors is wrong, therefore set back to default "
						<< endl << "min: " << min_load_factor << " | max: "
						<< max_load_factor << flush << endl;
			}
		}
		inline virtual ~HashTable() {

		}

		inline void insert(const V &value) {
//			size_t hashIdx = calculateIndex(value);
//			auto mapIt = hashTable.find(hashIdx);
//			// Hash key present in map
//			if (mapIt != hashTable.end()) {
//				vector<V&> chain = (*mapIt).second;
//				auto chainIt = find(chain.begin(), chain.end(), value);
//				// Value already present
//				if (chainIt == (*mapIt).second.end()) {
//					(*mapIt).second.push_back(value);
//					currentSize++;
//				}
//			}
//			// HashKey not found
//			else {
//				vector<V&> chain;
//				chain.push_back(value);
//				hashTable.insert(pair<size_t, vector<V&>>(hashIdx, chain));
//				currentSize++;
//			}
//			validateLoadFactor();
		}
		inline void erase(const V &value) {
			// Element present
			if (contains(value)) {
				size_t hashIdx = calculateIndex(value);
				vector<V&> chain = hashTable[hashIdx];
				auto chainIt = chain.find(value);
				// Value present in chain
				if (chainIt != chain.end()) {
					chain.erase(value);
					currentSize--;
				}
			}
			validateLoadFactor();
		}
		inline bool contains(const V &value) const {
			bool result = false;
			// Elements present
			if (size() > 0) {
				size_t hashIdx = calculateIndex(value);
				auto it = hashTable.find(hashIdx);
				// Hash key found
				if (it != hashTable.end()) {
					vector<V&> chain = (*it).second;
					auto chainIterator = chain.find(value);
					// Value present in chain
					result = (chainIterator != chain.end());
				}
			}
			return result;
		}
		inline void rehash(size_t new_n_buckets) {
//			// new map where to copy elements
//			map<size_t, vector<V&>, key_equal_function_type> newMap(equals);
//			// Iterate over all map entries
//			for_each(hashTable.begin(), hashTable.end(),
//					([&newMap, this](const pair<size_t, vector<V&>> p) {
//						vector<V&> chain = p.second;
//						// Iterate over all values of a hash key
//						for_each(chain.begin(), chain.end(), ([&newMap, this](const V value) {
//											size_t hashIdx = calculateIndex(value);
//											auto mapIt = newMap.find(hashIdx);
//											if(mapIt != newMap.end()) {
//												(*mapIt).second.push_back(value);
//											} else {
//												vector<V&> newChain;
//												newChain.push_back(value);
//												newMap[hashIdx] = newChain;
//											}
//										}));
//					}));

		}
		inline double load_factor() const {
			return currentCapacity / currentSize;
		}
		inline size_t size() const {
			return currentSize;
		}
		inline size_t capacity() {
			return currentCapacity;
		}

		inline bool empty() const {
			return size() == 0;
		}
		inline bool operator ==(const HashTable &other) const {
			// Same instance
			if (other == *this) {
				return true;
			}
			// Other instance with same size
			if (this->size() == other.size()) {
				bool result = true;
				auto mapIterator = this->hashTable.begin();
				while (result && (mapIterator != this->hashTable.end())) {
					vector<V&> chain = (*mapIterator).second;
					auto chainIterator = chain.begin();
					while (result && (chainIterator != chain.end())) {
						result = other.contains((*chainIterator));
					}
				}
				return result;
			}
			// Not same instance and not same size
			return false;
		}

		typedef std::iterator<std::bidirectional_iterator_tag, value_type,
				difference_type, const_pointer, const_reference> iterator_base;

		class const_iterator: public iterator_base {
			public:
				typedef typename iterator_base::difference_type difference_type;
				typedef typename iterator_base::iterator_category iterator_category;
				typedef typename iterator_base::pointer pointer;
				typedef typename iterator_base::reference reference;
				typedef typename iterator_base::value_type value_type;

				bool operator ==(const_iterator const & rhs) const;
				bool operator !=(const_iterator const & rhs) const;

				reference operator *() const;
				pointer operator ->() const;

				const_iterator & operator ++();
				const_iterator & operator --();

				const_iterator operator ++(int);
				const_iterator operator --(int);

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
std::ostream & operator <<(std::ostream & os, const HashTable<V, H, C> &ht);

#endif // HashTable_hpp
