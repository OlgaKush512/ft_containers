#include <vector>
#include <iostream>

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

		

		void reserve(size_t n)
		{
			if (n <= cap)
			return;
			T* new_arr = new T[n];
			for (size_t i = 0; i < sz; ++i)
				new_arr[i] = arr[i];
			delete [] arr;
			arr = new_arr;
			cap = n;
		}

		void resize(size_t n, const T& value = T())
		{
			if (n > cap)
				reserve(n);
			for (size_t i = sz; i < n; ++i)
				arr[i];
			if (n < sz)
				sz = n;
		}
		void push_back(const T& value)
		{
			if (cap == sz)
			{
				reserve(2 * sz);
			}
			arr[sz] = value;
			++sz;
		}

		void pop_back()
		{
			--sz;
		}
};

int main()
{
	std::vector<int> v(10);
	v.size();
	v.capacity();


}
