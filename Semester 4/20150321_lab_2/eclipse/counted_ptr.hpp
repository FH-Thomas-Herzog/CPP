#ifndef COUNTED_PTR_HPP_INCLUDED
#define COUNTED_PTR_HPP_INCLUDED

template<typename T>
class counted_pointer {
	private:
		struct counter {
				T* ptr;
				unsigned int count;
				counter(T* ptr, unsigned int count = 1) :
						ptr(ptr), count(count) {
				}
		};

		counter* ref_counter;

		inline void aquire(counter* c) {
			ref_counter = c;
			if (c != nullptr) {
				++(c->count);
			}
		}

		inline void release() {
			if (ref_counter == nullptr) {
				return;
			}
			ref_counter->count--;
			if (ref_counter->count == 0) {
				delete ref_counter->ptr;
				delete ref_counter;
				ref_counter = nullptr;
			}
		}

	public:
		typedef T value_type;

		explicit counted_pointer(T* ptr = nullptr) {
			if (ptr != nullptr) {
				ref_counter = new counter(ptr);
			}
		}

		counted_pointer(const counted_pointer& ptr) {
			aquire(ptr.ref_counter);
		}

		~counted_pointer() {
			release();
		}

		inline counted_pointer& operator=(const counted_pointer& ptr) {
			if (this != &ptr) {
				release();
				aquire(ptr.ref_counter);
			}
			return *this;
		}

		T& operator*() {
			return *ref_counter->ptr;
		}

		const T& operator*() const {
			return *ref_counter->ptr;
		}

		T* operator->() {
			return *ref_counter->ptr;
		}
};

#endif // COUNTED_PTR_HPP_INCLUDED
