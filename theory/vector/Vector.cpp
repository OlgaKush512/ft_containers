#include <vector>
#include <iostream>
#include <exception>
#include <stdint.h> //<cstdint> in C++11
#include <memory>

template <typename T>
class Vector
{
	private:
		T* arr;
		size_t sz;
		size_t cap;
	public:

		//size_t size() const;
		// size_t capacity() const;

		

		void reserve(size_t n) // pour apres voir std::uninitialized_copy;
		{
			if (n <= cap)
			return;
			// T* new_arr = new T[n]; mauvais. s'il n'y pas de default constructeur ou bien si les objets son comme threads?
			T* new_arr = reinterpret_cast<T*>(new int8_t[n * sizeof(T)]); //(new char[n * sizeof(T)])
			size_t i = 0;
			try
			{
				std::uninitialized_copy(arr, arr + sz, new_arr);
			}
			catch (...)
			{
				delete [] reinterpet_cast<int8_t*>(new_arr);
				throw;
			}

			// try
			// {
			// 	for (size_t i = 0; i < sz; ++i)
			// 		new (new_arr + i) T(arr[i]);// placement new
			// 		// new_arr[i] = arr[i];
			// }
			// catch(....)
			// {
			// 	for (size_t j = 0; j < i; ++j)
			// 		(new_arr + i)->~T();//arr[i].~T()
			// 	delete [] reinterpet_cast<int8_t*>(new_arr);
			// 	throw;
			// }
			for (size_t i = 0; i < sz; ++i)
				(arr + i)->~T();//arr[i].~T()
			// delete [] arr;
			delete [] reinterpet_cast<int8_t*>(arr);
			arr = new_arr;
			cap = n;
		}

		void resize(size_t n, const T& value = T())
		{
			if (n > cap)
				reserve(n);
			for (size_t i = sz; i < n; ++i)
				new(arr + i) T(value);
			if (n < sz)
				sz = n;
		}
		void push_back(const T& value)
		{
			if (cap == sz)
			{
				reserve(2 * sz);
			}
			new(arr + sz) T(value);
			// arr[sz] = value;
			++sz;
		}

		void pop_back()
		{
			(arr + sz)->~T();
			--sz;
		}

		T& operator[](size_t i)
		{
			return (arr[i]);
		}

		const T& operator[](size_t i) const
		{
			return (arr[i]);
		}

		T& at(size_t i) const
		{
			if (i >= sz)
				throw std::out_of_range{"..."};
			return (arr[i]);
		}
};

int main()
{
	std::vector<bool> vb(10, false);
	vb[5] = true;
	// std::vector<int> v(10);
	// v.size();
	// v.capacity();


}
