# ifndef VECTOR_HPP
# define VECTOR_HPP

// # include <vector>
# include <memory>
# include <stdexcept>
# include <stdint.h>


namespace ft
{
	template<class T, class A = allocator<T> >
	class vector
	{
		public:

			typedef A										allocator_type;
			typedef typename A::pointer						pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::value_type					value_type;

			typedef T0										iterator;
			typedef T1										const_iterator;
			typedef T2										size_type;
			typedef T3										difference_type;

			typedef reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef reverse_iterator<iterator>				reverse_iterator;


			// constructors

			vector() : {};
			explicit vector( const allocator_type& alloc );
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator());

			vector(const vector& other): _size(other._size), _cap(other._cap), _alloc(other._alloc)
			{
				for (size_t i = 0; i < _size; ++i)
					_array[i] = other._array[i];
			};

			/*vector& operator=( const vector& other )
			{
				_c = other._c;
				return (*this);
			}*/

			~vector() {};

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			void assign( size_type count, const T& value );

			//element access

			reference at(size_t i) const
			{
				if (i >= _size)
					throw std::out_of_range{"..."};
				return (_array[i]);
			}

			const_reference at(size_t i) const
			{
				if (i >= _size)
					throw std::out_of_range{"..."};
				return (_array[i]);
			}

			reference operator[](size_t i)
			{
				return (_array[i]);
			}

			const_reference operator[](size_t i) const
			{
				return (_array[i]);
			}

			reference front()
			{
				if (!_size)
					throw std::out_of_range{"The vector is empty"};
				return (_array[0]);
			}

			const_reference front() const
			{
				if (!_size)
					throw std::out_of_range{"The vector is empty"};
				return (_array[0]);
			}

			reference back()
			{
				if (!_size)
					throw std::out_of_range{"The vector is empty"};
				return (_array[_size - 1]);
			}

			const_reference back() const
			{
				if (!_size)
					throw std::out_of_range{"The vector is empty"};
				return (_array[_size - 1]);
			}

			pointer data()
			{
				if (!_size)
					return (NULL);
				return (_array);
			}

			const_pointer data() const
			{
				if (!_size)
					return (NULL);
				return (_array);
			}
			
			// capacity

			bool empty() const
			{
				if (!_size)
					return (true);
				return (false);
			}

			size_t size() const
			{
				return (_size);
			}

			size_t max_size() const
			{
				return (allocator_type.max_size());
			}

			size_t capacity() const
			{
				return (_cap);
			}

			void reserve(size_t n) /*If new_cap is greater than capacity(), 
			all iterators, including the past-the-end iterator, 
			and all references to the elements are invalidated.*/
		{
			if (n <= _cap)
			return;
			T* new_arr = reinterpret_cast<T*>(new int8_t[n * sizeof(T)]); //(new char[n * sizeof(T)])
			size_t i = 0;
			try
			{
				std::uninitialized_copy(_array, _array + _size, new_arr);
			}
			catch (...)
			{
				delete [] reinterpet_cast<int8_t*>(new_arr);
				throw;
			}

			// try
			// {
			// 	for (size_t i = 0; i < _size; ++i)
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
			for (size_t i = 0; i < _size; ++i)
				(_array + i)->~T();//arr[i].~T()
			delete [] reinterpet_cast<int8_t*>(_array);
			_array = new_arr;
			_cap = n;
		}

		// modifiers

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
			

		private:

			T*				_array;
			size_t			_size;
			size_t			_cap;
			allocator_type	_alloc;
		};
}

# endif
