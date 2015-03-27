#ifndef HashTable_hpp
#define HashTable_hpp

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <map>
#include <vector>

template<typename V, typename H, typename C>
class HashTable;

template<typename V, typename H, typename C>
std::ostream & operator <<(std::ostream & os, const HashTable<V, H, C> &ht);

template<typename V, typename H, typename C>
class HashTable {
		friend std::ostream & operator <<<V, H, C>(std::ostream & os,
				const HashTable<V, H, C> &ht);

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

		//##############################################
		// Members
		//##############################################
		/**
		 * This container will realize the has table where the has key is mapped to a chain of elements.
		 * These chained elements are these elements which have the same hash key.
		 */
		std::map<std::size_t, std::vector<V>, key_equal_function_type> hashTableMap;
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
		void validateLoadFactor();

		/**
		 * Calculates the has table index out of the calculated hash
		 * @param
		 * 		V& value: the value to get proper index for
		 * @return
		 * 		the calculates hash index for the hash table
		 */
		std::size_t calculateIndex(V& value);

		HashTable(size_t n_buckets = 10, hash_function_type hasher =
				std::hash<V>(), key_equal_function_type equals =
				std::equal_to<V>(), double max_load_factor = 0.8,
				double min_load_factor = 0.2);
		virtual ~HashTable();

		void insert(const V &value);
		void erase(const V &value);
		bool contains(const V &value) const;
		void rehash(size_t new_n_buckets);
		double load_factor() const;
		size_t size() const;
		size_t capacity();
		bool empty() const;
		bool operator ==(const HashTable &other) const;

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
