# ifndef VECTOR_HPP
# define VECTOR_HPP

// # include <vector>
# include <memory>
# include <stdexcept>
# include <stdint.h>


namespace ft
{
	template<class T, class A = std::allocator<T> >
	class vector
	{
		class iterator<> : ft::iterator<ft::random_access_iterator_tag,

		{
			

		}

		class const_iterator<>
		{

		}
		public:

			typedef A										allocator_type;
			typedef typename A::pointer						pointer;
			typedef typename A::const_pointer				const_pointer;
			typedef typename A::reference					reference;
			typedef typename A::const_reference				const_reference;
			typedef typename A::value_type					value_type;

			//UTILITY
			/*typedef T0									iterator;
			typedef T1										const_iterator;
			typedef T2										size_type;
			typedef T3										difference_type;

			typedef reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef reverse_iterator<iterator>				reverse_iterator;*/ 


			// constructors

			vector() : _array(0), _size(0), _cap(0), _alloc(allocator_type()) {} ;

			explicit vector( const allocator_type& alloc ) : _array(0), _size(0), _cap(0), _alloc(alloc) {} ;

			explicit vector(size_t count, const T& value = T(), const allocator_type& alloc = allocator_type()) : 
			_size(count), _cap(count), _alloc(alloc)
			{
				_array = _alloc.allocate(count);
				for (size_t i = 0; i < _size; ++i)
				{
					_alloc.construct(_array + i, value);
				}
			}

			template< class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc = allocator_type()); //ITERATOR

			vector(const vector& other): _size(other._size), _cap(other._cap), _alloc(other._alloc)
			{
				_array = _alloc.allocate(_size);
				for (size_t i = 0; i < _size; ++i)
				{
					_alloc.construct(_array + i,  other._array[i]);
				}
			};

			vector& operator=( const vector& other )
			{
				clear()
				reserve(other._cap);
				_size = other._size;
				for (size_t i = 0; i < _size; ++i)
				{
					_alloc.construct(_array + i, other._array[i]);
				}
				return (*this);
			}

			~vector()
			{
				if (_cap)
				{
					clear();
					_alloc.deallocate(_array, _cap);
				}
			} 

			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			void assign( size_t count, const T& value );

			//element access

			reference at(size_t i) 
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
				return (_alloc.max_size());
			};

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
				pointer new_arr = _alloc.allocate(n);
				size_t i = 0;
				for (; i < _size; ++i)
				{
					_alloc.construct(new_arr + i, _array[i]);
				}
				for (i = 0; i < _size; ++i)
					_alloc.destroy(_array + i);
				_alloc.deallocate(_array, n);
				_array = new_arr;
				_cap = n;
			}

			// modifiers

			void clear()
			{
				if (_size != 0)
				{
					for (size_t i = 0; i < _size; ++i)
						_alloc.destroy(_array + i);
					_size = 0;
				}
			}

			// INSERT
			/*iterator insert( iterator pos, const T& value );
			void insert( iterator pos, size_type count, const T& value );
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last );*/

			// ERASE
			/*iterator erase( iterator pos );
			iterator erase( iterator first, iterator last );*/

			void swap( vector& other )
			{
				pointer	array_temp = _array;
				size_t size_temp(_size);
				size_t cap_temp(_cap);

				_array = other._array;
				_size = other._size;
				_cap = other._cap;

				other._array = array_temp;
				other._size = size_temp;
				other._cap = cap_temp;
			}


			void resize(size_t n, const T& value = T())
			{
				if (n > _cap)
					reserve(n);
				for (size_t i = _size; i < n; ++i)
					_alloc.construct(_array + i, value);
				if (n < _size)
				{
					for (int j = _size - (_size - n); j < _size; ++j)
						_alloc.destroy(_array + j);
				}
				_size = n;
			}
			
			void push_back(const T& value)
			{
				if (_size == 0) // mette en reserve
					reserve(1);
				else if (_cap == _size)
				{
					reserve(2 * _cap);
				}
				_alloc.construct(_array + _size, value);
				++_size;
			}

			void pop_back()
			{
				_alloc.destroy(_array + (_size - 1));
			}
			
			// NON_MEMBER FONCTIONS

			template< class T, class Alloc >
			friend bool operator==(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);

			template< class T, class Alloc >
			friend bool operator!=(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);

			/*template< class T, class Alloc >
			friend bool operator<(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);

			template< class T, class Alloc >
			friend bool operator<=(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);
			
			template< class T, class Alloc >
			friend bool operator>(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);
			
			template< class T, class Alloc >
			friend bool operator>=(const ft::vector<T,Alloc>& lhs,
							const ft::vector<T,Alloc>& rhs);*/

		private:

			pointer			_array;
			size_t			_size;
			size_t			_cap;
			allocator_type	_alloc;
	};


		template< class T, class Alloc >
		bool operator==(const ft::vector<T,Alloc>& lhs,
						const ft::vector<T,Alloc>& rhs)
		{
			if (lhs._size != rhs._size)
				return (false);
			for (size_t i = 0; i < lhs._size; ++i)
			{
				if (lhs._array[i] != rhs._array[i])
					return (false);
			}
			return (true);
		}


		template< class T, class Alloc >
		bool operator!=(const ft::vector<T,Alloc>& lhs,
						const ft::vector<T,Alloc>& rhs)
		{
			if (lhs._size != rhs._size)
				return (true);
			for (size_t i = 0; i < lhs._size; ++i)
			{
				if (lhs._array[i] != rhs._array[i])
					return (true);
			}
			return (false);
		}

		/*template< class T, class Alloc >
		friend bool operator<(const ft::vector<T,Alloc>& lhs,
						const ft::vector<T,Alloc>& rhs);

		template< class T, class Alloc >
		friend bool operator<=(const ft::vector<T,Alloc>& lhs,
						const ft::vector<T,Alloc>& rhs);
		
		template< class T, class Alloc >
		friend bool operator>(const ft::vector<T,Alloc>& lhs,
						const ft::vector<T,Alloc>& rhs);
		
		template< class T, class Alloc >
		friend bool operator>=(const ft::vector<T,Alloc>& lhs,
						const ft::vector<T,Alloc>& rhs);*/
}

# endif
