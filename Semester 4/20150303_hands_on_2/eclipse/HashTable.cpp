/*
 * HashTable.cpp
 *
 *  Created on: Mar 27, 2015
 *      Author: cchet
 */
#include "HashTable.hpp"
#include <stdio.h>

using namespace std;

//##############################################
// Private methods
//##############################################
template<typename V, typename H, typename C>
void HashTable<V, H, C>::validateLoadFactor() {
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

template<typename V, typename H, typename C>
size_t HashTable<V, H, C>::calculateIndex(V& value) {
	return (hasher(value) % currentCapacity);
}

//##############################################
// Constructor and destructor
//##############################################
template<typename V, typename H, typename C>
HashTable<V, H, C>::HashTable(size_t n_buckets, hash_function_type hasher,
		key_equal_function_type equals, double max_load_factor,
		double min_load_factor) :
		currentCapacity(n_buckets), hasher(hasher), equals(equals), minLoadFactor(
				min_load_factor), maxLoadFactor(max_load_factor), currentSize(0) {
// Handle invalid capacity
	if (currentCapacity < 10) {
		currentCapacity = 10;
		cout << "Capacity of " << n_buckets
				<< " to small therefore set to default" << flush << endl;
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
// init map with given comparator
	hashTableMap = map<size_t, vector<V>, key_equal_function_type>(equals);
}

template<typename V, typename H, typename C>
HashTable<V, H, C>::~HashTable() {
// No dynamic members, therefore nothing to do
}

//##############################################
// Public methods
//##############################################
template<typename V, typename H, typename C>
void HashTable<V, H, C>::insert(const V &value) {
	size_t hashIdx = calculateIndex(value);
	auto mapIt = hashTableMap.find(hashIdx);
// Hash key present in map
	if (mapIt != hashTableMap.end()) {
		auto chainIt = (*mapIt).second.find(value);
		// Value already present
		if (chainIt == (*mapIt).second.end()) {
			(*mapIt).second.insert(value);
			currentSize++;
		}
	}
// HashKey not found
	else {
		vector<V> chain;
		chain.isnert(value);
		hashTableMap[hashIdx] = chain;
		currentSize++;
	}
	validateLoadFactor();
}

template<typename V, typename H, typename C>
void HashTable<V, H, C>::erase(const V &value) {
// Element present
	if (contains(value)) {
		size_t hashIdx = calculateIndex(value);
		vector<V> chain = hashTableMap[hashIdx];
		auto chainIt = chain.find(value);
		// Value present in chain
		if (chainIt != chain.end()) {
			chain.erase(value);
			currentSize--;
		}
	}
	validateLoadFactor();
}

template<typename V, typename H, typename C>
bool HashTable<V, H, C>::contains(const V &value) const {
	bool result = false;
// Elements present
	if (size() > 0) {
		size_t hashIdx = calculateIndex(value);
		auto it = hashTableMap.find(hashIdx);
		// Hash key found
		if (it != hashTableMap.end()) {
			vector<V> chain = (*it).second;
			auto chainIterator = chain.find(value);
			// Value present in chain
			result = (chainIterator != chain.end());
		}
	}
	return result;
}

template<typename V, typename H, typename C>
void HashTable<V, H, C>::rehash(size_t new_n_buckets) {
// new map where to copy elements
	map<size_t, vector<V>, key_equal_function_type> newMap(equals);
// Iterate over all map entries
	for_each(hashTableMap.begin(), hashTableMap.end(),
			([&newMap, this](const pair<size_t, vector<V>> p) {
				vector<V> chain = p.second;
				// Iterate over all values of a hash key
				for_each(chain.begin(), chain.end(), ([&newMap, this](const V value) {
									size_t hashIdx = calculateIndex(value);
									auto mapIt = newMap.find(hashIdx);
									if(mapIt != newMap.end()) {
										(*mapIt).second.insert(value);
									} else {
										vector<V> newChain;
										newChain.insert(value);
										newMap[hashIdx] = newChain;
									}
								}));
			}));

}

template<typename V, typename H, typename C>
double HashTable<V, H, C>::load_factor() const {
	return currentCapacity / currentSize;
}

template<typename V, typename H, typename C>
typename HashTable<V, H, C>::size_t HashTable<V, H, C>::size() const {
	return currentSize;
}

template<typename V, typename H, typename C>
typename HashTable<V, H, C>::size_t HashTable<V, H, C>::capacity() {
	return currentCapacity;
}

template<typename V, typename H, typename C>
bool HashTable<V, H, C>::empty() const {
	return size() == 0;
}

template<typename V, typename H, typename C>
bool HashTable<V, H, C>::operator ==(const HashTable &other) const {
// Same instance
	if (other == *this) {
		return true;
	}
// Other instance with same size
	if (this->size() == other.size()) {
		bool result = true;
		auto mapIterator = this->hashTableMap.begin();
		while (result && (mapIterator != this->hashTableMap.end())) {
			vector<V> chain = (*mapIterator).second;
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
